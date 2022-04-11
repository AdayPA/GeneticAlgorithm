#include "../lib/population.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
std::string trim(const std::string& value) {
  const std::string whitespace = " \t\r\n";
  const std::size_t start = value.find_first_not_of(whitespace);
  if (start == std::string::npos) {
    return "";
  }
  const std::size_t end = value.find_last_not_of(whitespace);
  return value.substr(start, end - start + 1);
}

std::size_t parseSize(const std::string& value, const std::string& field) {
  const std::string cleaned = trim(value);
  if (cleaned.empty() || cleaned[0] == '-') {
    throw std::invalid_argument("Invalid numeric value for " + field + ": " + value);
  }

  std::size_t consumed = 0;
  const unsigned long result = std::stoul(cleaned, &consumed);
  if (consumed != cleaned.size()) {
    throw std::invalid_argument("Invalid numeric value for " + field + ": " + value);
  }
  return static_cast<std::size_t>(result);
}

double parseDouble(const std::string& value, const std::string& field) {
  const std::string cleaned = trim(value);
  std::size_t consumed = 0;
  const double result = std::stod(cleaned, &consumed);
  if (consumed != cleaned.size()) {
    throw std::invalid_argument("Invalid decimal value for " + field + ": " + value);
  }
  return result;
}
}

Population::Population(const std::string& input_file, unsigned int seed)
    : config_(loadConfig(input_file)),
      rng_(seed),
      x_(0.0),
      chromosome_size_(0),
      eval_fun_(nullptr) {
  validateConfig();
  const double domain = config_.max_value - config_.min_value;
  const double scaled_domain = domain * std::pow(10.0, static_cast<double>(config_.precision));
  chromosome_size_ = std::max<std::size_t>(2, static_cast<std::size_t>(std::ceil(std::log2(scaled_domain + 1.0))));

  population_.reserve(config_.population_size);
  for (std::size_t i = 0; i < config_.population_size; i++) {
    population_.emplace_back(chromosome_size_, config_.min_value, config_.max_value, config_.precision, rng_);
  }
  translateFunction();
}

Population::~Population() {
  te_free(eval_fun_);
}

void Population::run(std::size_t generations, std::ostream& os) {
  calcFitness();
  printPopulation(os, "Initial population");

  for (std::size_t i = 0; i < generations; i++) {
    doCycle();
    printPopulation(os, "Generation " + std::to_string(i + 1));
  }
}

Population::Config Population::loadConfig(const std::string& filename) const {
  std::ifstream inputfile(filename);
  if (!inputfile) {
    throw std::runtime_error("Unable to open input file: " + filename);
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputfile, line)) {
    if (!trim(line).empty()) {
      lines.push_back(trim(line));
    }
  }
  if (lines.size() < 9) {
    throw std::runtime_error("Input file must contain 9 non-empty lines");
  }

  Config config{};
  config.population_size = parseSize(lines[0], "population size");
  config.variable_count = parseSize(lines[1], "variable count");
  config.variable = lines[2];
  config.precision = static_cast<int>(parseSize(lines[3], "precision"));
  config.fitness_function = lines[4];

  const std::vector<std::string> min_max = split(lines[5]);
  if (min_max.size() != 2) {
    throw std::runtime_error("Range must contain two values: min max");
  }
  config.min_value = parseDouble(min_max[0], "minimum range");
  config.max_value = parseDouble(min_max[1], "maximum range");

  if (lines[6] == "single-point") {
    config.crossover_type = CrossoverType::SinglePoint;
  } else if (lines[6] == "two-point") {
    config.crossover_type = CrossoverType::TwoPoint;
  } else {
    throw std::runtime_error("Unsupported crossover type: " + lines[6]);
  }

  if (lines[7] == "roulette") {
    config.selection_type = SelectionType::Roulette;
  } else {
    throw std::runtime_error("Unsupported selection type: " + lines[7]);
  }

  const std::vector<std::string> points = split(lines[8]);
  for (const std::string& point : points) {
    config.crossover_points.push_back(parseSize(point, "crossover point"));
  }
  return config;
}

void Population::validateConfig(void) const {
  if (config_.population_size < 2) {
    throw std::runtime_error("Population size must be at least 2");
  }
  if (config_.variable_count != 1 || config_.variable != "x") {
    throw std::runtime_error("This implementation supports exactly one variable named x");
  }
  if (config_.max_value <= config_.min_value) {
    throw std::runtime_error("Range maximum must be greater than range minimum");
  }
  if (config_.precision < 0) {
    throw std::runtime_error("Precision must be zero or greater");
  }
}

void Population::doCycle(void) {
  selection();
  crossover();
  calcFitness();
  getNextGeneration();
  calcFitness();
}

void Population::calcFitness(void) {
  for (std::size_t i = 0; i < population_.size(); i++) {
    x_ = population_[i].getFenotype();
    const double fitness = te_eval(eval_fun_);
    if (!std::isfinite(fitness)) {
      throw std::runtime_error("Fitness function returned a non-finite value for x=" + std::to_string(x_));
    }
    population_[i].setFitness(fitness);
  }
}

void Population::printPopulation(std::ostream& os, const std::string& title) const {
  os << "\n" << title << ":\n";
  os << std::left << std::setw(static_cast<int>(chromosome_size_ + 4)) << "Chromosome"
     << std::right << std::setw(14) << "Phenotype"
     << std::setw(14) << "Fitness" << "\n";

  for (const Individual& individual : population_) {
    individual.printIndividual(os);
    os << std::right << std::setw(18) << std::fixed << std::setprecision(config_.precision) << individual.getFenotype()
       << std::setw(14) << std::setprecision(6) << individual.getFitness() << "\n";
  }
}

void Population::crossover(void) {
  if (config_.crossover_type == CrossoverType::TwoPoint) {
    doTwoPoint();
  }
  else if (config_.crossover_type == CrossoverType::SinglePoint) {
    doSinglePoint();
  }
}

void Population::selection(void) {
  selected_parents_.clear();
  if (config_.selection_type == SelectionType::Roulette) {
    const std::size_t parent_count = std::max<std::size_t>(2, (config_.population_size / 2) * 2);
    selected_parents_ = doRoulette(population_, std::min(parent_count, population_.size()));
  }
}

void Population::doTwoPoint(void) {
  if (config_.crossover_points.size() != 2) {
    throw std::runtime_error("Two-point crossover requires two crossover points");
  }
  const std::size_t first = config_.crossover_points[0];
  const std::size_t second = config_.crossover_points[1];
  if (first == 0 || second <= first || second >= chromosome_size_) {
    throw std::runtime_error("Two-point crossover requires 0 < first < second < chromosome size");
  }

  for (std::size_t i = 0; i + 1 < selected_parents_.size(); i += 2) {
    const std::vector<Individual> children = selected_parents_[i].doTwoPoint(selected_parents_[i + 1], first, second);
    population_.insert(population_.end(), children.begin(), children.end());
  }
}

void Population::doSinglePoint(void) {
  if (config_.crossover_points.size() != 1) {
    throw std::runtime_error("Single-point crossover requires one crossover point");
  }
  const std::size_t section = config_.crossover_points[0];
  if (section == 0 || section >= chromosome_size_) {
    throw std::runtime_error("Single-point crossover requires 0 < point < chromosome size");
  }

  for (std::size_t i = 0; i + 1 < selected_parents_.size(); i += 2) {
    const std::vector<Individual> children = selected_parents_[i].doSinglePoint(selected_parents_[i + 1], section);
    population_.insert(population_.end(), children.begin(), children.end());
  }
}

void Population::getNextGeneration(void) {
  population_ = doRoulette(population_, config_.population_size);
}

std::vector<Individual> Population::doRoulette(const std::vector<Individual>& source, std::size_t count) {
  std::vector<std::size_t> candidates(source.size());
  std::iota(candidates.begin(), candidates.end(), 0);

  std::vector<Individual> selected;
  selected.reserve(count);
  while (!candidates.empty() && selected.size() < count) {
    std::vector<double> weights;
    weights.reserve(candidates.size());
    const double floor = rouletteWeightFloor(source);
    for (const std::size_t candidate : candidates) {
      weights.push_back((source[candidate].getFitness() - floor) + 1.0);
    }

    std::discrete_distribution<std::size_t> distribution(weights.begin(), weights.end());
    const std::size_t selected_position = distribution(rng_);
    selected.push_back(source[candidates[selected_position]]);
    candidates.erase(candidates.begin() + static_cast<std::ptrdiff_t>(selected_position));
  }
  return selected;
}

double Population::rouletteWeightFloor(const std::vector<Individual>& source) const {
  double min_fitness = std::numeric_limits<double>::infinity();
  for (const Individual& individual : source) {
    min_fitness = std::min(min_fitness, individual.getFitness());
  }
  return std::isfinite(min_fitness) ? min_fitness : 0.0;
}

void Population::translateFunction(void) {
  int error = 0;
  const char *expression = config_.fitness_function.c_str();
  te_variable vars[] = {{"x", &x_, TE_VARIABLE, nullptr}};
  eval_fun_ = te_compile(expression, vars, 1, &error);
  if (eval_fun_ == nullptr) {
    throw std::runtime_error("Unable to compile fitness function near character " + std::to_string(error));
  }
}

std::vector<std::string> Population::split(const std::string& str) const {
  std::vector<std::string> tokens;
  std::istringstream stream(str);
  std::string token;
  while (stream >> token) {
    tokens.push_back(token);
  }
  return tokens;
}
