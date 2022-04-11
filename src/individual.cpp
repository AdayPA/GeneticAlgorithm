#include "../lib/individual.hpp"

#include <cmath>
#include <iostream>
#include <utility>

Individual::Individual()
    : fenotype_(0.0),
      fitness_(0.0),
      min_value_(0.0),
      max_value_(0.0),
      chromosome_value_(0),
      precision_(0) {}

Individual::Individual(std::size_t size, double min_value, double max_value, int precision, std::mt19937& rng)
    : chromosome_(size, rng),
      fenotype_(0.0),
      fitness_(0.0),
      min_value_(min_value),
      max_value_(max_value),
      chromosome_value_(0),
      precision_(precision) {
  calcFenotype();
  normalize();
}

Individual::Individual(Chromosome chromosome, double min_value, double max_value, int precision)
    : chromosome_(std::move(chromosome)),
      fenotype_(0.0),
      fitness_(0.0),
      min_value_(min_value),
      max_value_(max_value),
      chromosome_value_(0),
      precision_(precision) {
  calcFenotype();
  normalize();
}

Individual::~Individual() {}

unsigned long long Individual::getValue(void) const {
  return chromosome_value_;
}

std::size_t Individual::getSize(void) const {
  return chromosome_.getSize();
}

int Individual::getPrecision(void) const {
  return precision_;
}

double Individual::getMinValue(void) const {
  return min_value_;
}

double Individual::getMaxValue(void) const {
  return max_value_;
}

double Individual::getFenotype(void) const {
  return fenotype_;
}

double Individual::getFitness(void) const {
  return fitness_;
}

void Individual::setFitness(double fitness) {
  fitness_ = fitness;
}

std::vector<Individual> Individual::doSinglePoint(const Individual& p1, std::size_t section) const {
  std::vector<bool> offspring1;
  std::vector<bool> offspring2;
  offspring1.reserve(getSize());
  offspring2.reserve(getSize());
  for (std::size_t i = 0; i < section; i++) {
    offspring1.push_back(p1.getGen(i));
    offspring2.push_back(this->getGen(i));
  }
  for (std::size_t i = section; i < p1.getSize(); i++) {
    offspring1.push_back(this->getGen(i));
    offspring2.push_back(p1.getGen(i));
  }
  std::vector<Individual> result;
  result.emplace_back(Chromosome(offspring1), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  result.emplace_back(Chromosome(offspring2), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  return result;
}

std::vector<Individual> Individual::doTwoPoint(const Individual& p1, std::size_t first, std::size_t second) const {
  std::vector<bool> offspring1;
  std::vector<bool> offspring2;
  offspring1.reserve(getSize());
  offspring2.reserve(getSize());
  for (std::size_t i = 0; i < first; i++) {
    offspring1.push_back(this->getGen(i));
    offspring2.push_back(p1.getGen(i));
  }
  for (std::size_t i = first; i < second; i++) {
    offspring1.push_back(p1.getGen(i));
    offspring2.push_back(this->getGen(i));
  }
  for (std::size_t i = second; i < getSize(); i++) {
    offspring1.push_back(this->getGen(i));
    offspring2.push_back(p1.getGen(i));
  }
  std::vector<Individual> result;
  result.emplace_back(Chromosome(offspring1), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  result.emplace_back(Chromosome(offspring2), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  return result;
}

bool Individual::getGen(std::size_t pos) const {
  return chromosome_.getValue(pos);
}

void Individual::calcFenotype(void) {
  chromosome_value_ = 0;
  for (std::size_t i = 0; i < chromosome_.getSize(); i++) {
    chromosome_value_ = (chromosome_value_ << 1) | static_cast<unsigned long long>(chromosome_.getValue(i));
  }
}

void Individual::normalize(void) {
  const double encoded_max = std::pow(2.0, static_cast<double>(chromosome_.getSize())) - 1.0;
  if (encoded_max <= 0.0) {
    fenotype_ = min_value_;
    return;
  }

  fenotype_ = min_value_ + (static_cast<double>(chromosome_value_) * (max_value_ - min_value_) / encoded_max);
  if (precision_ >= 0) {
    const double scale = std::pow(10.0, static_cast<double>(precision_));
    fenotype_ = std::round(fenotype_ * scale) / scale;
  }
}

void Individual::printIndividual(std::ostream& os) const {
  for (std::size_t i = 0; i < chromosome_.getSize(); i++) {
    os << chromosome_.getValue(i);
  }
}
