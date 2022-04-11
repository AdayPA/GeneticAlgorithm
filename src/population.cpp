#ifndef POPULATION_CPP_
#define POPULATION_CPP_

#include "../lib/population.hpp"

#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>


Population::Population( std::string input_file) {
  population_size_ = std::stoi(Get_line(input_file,1));
  output_size_ = std::stoi(Get_line(input_file,2));
  variable_ = (Get_line(input_file,3));
  precision_ = std::stoi(Get_line(input_file,4));
  eval_function_ = Get_line(input_file,5);
  domain_func_ = Get_line(input_file,6);
  crossover_ = Get_line(input_file,7);
  selection_ = Get_line(input_file,8);
  crossover_section_ = Get_line(input_file,9);
  std::vector<std::string> min_max = Split(domain_func_, " ");
  domain_ = std::stof(min_max[1]) - std::stof(min_max[0]);
  min_value_ = std::stof(min_max[0]);
  max_value_ = std::stof(min_max[1]);
  if (precision_ == 1) {
    chromosome_size_ = (int)ceil(log2(domain_ ));
  } else {
    chromosome_size_ = (int)ceil(log2(domain_ * pow(10,precision_)));
  }
  // ** INIT ** //
  for (int i = 0; i < population_size_; i++) {
    population_.push_back(Individual(chromosome_size_, min_value_, max_value_, precision_));
  }
  translateFunction();

  for (int i = 0; i < 4; i++) {
    printPopulation(3);
  doCycle();
  }
  printPopulation(3);

}

Population::~Population(){
  te_free(eval_fun_);
}

void Population::getNextGeneration(void) {
  std::vector<std::vector<float>> chance;
  std::vector<float> temp;
  std::vector<Individual> new_population;
  for (int i = 0; i < population_.size(); i++) {
    temp.push_back(population_[i].getFitness() / total_fitness_);
    temp.push_back(i);
    chance.push_back(temp);
    temp.clear();
  }
  std::sort(chance.begin(), chance.end());
  std::reverse(chance.begin(), chance.end());
  for (int i = 1; i < chance.size(); i++) {
    chance[i][0] = chance[i][0] + chance[i-1][0] ;
  }
  for (int i = 0 ; i < (population_.size() - selected_parents_.size()) ; i++) {
    float random = (double) rand() / (RAND_MAX);
    for (int j = 0; j < chance.size(); j++) {
      if (random < chance[j][0]) {
        new_population.push_back(population_[chance[j][1]]);
        chance.erase(chance.begin() + j);
        j = chance.size();
      }
    }
  }
  population_ = new_population;
}

void Population::doCycle(void) {
  // ** CALC FITNESS ** //
  calcFitness();
  // ** SELECTION **//
  selection();
  // ** CROSSOVER **//
  crossover();
  calcFitness();
  // ** NEW GENERATION **//
  getNextGeneration();
}

void Population::calcFitness(void) {
  total_fitness_ = 0.0;
  for (int i = 0; i < population_.size(); i++) {
    x_ = population_[i].getFenotype();
    population_[i].setFitness(te_eval(eval_fun_));
    total_fitness_ += te_eval(eval_fun_);
  }
}

void Population::printSelectedParent(void) {
  std::cout << "Selected parents:\n"; 
  std::cout << "Chromosome" << std::setw(20) << "Fenotype"  << std::setw(18) << "Fitness" << "\n";
  for (int  i = 0; i < selected_parents_.size(); i++) {
    selected_parents_[i].printIndividual();
    std::cout << std::setw(20) << selected_parents_[i].getFenotype() << std::setw(20) << selected_parents_[i].getFitness() << "\n";
  }
}

void Population::printPopulation(int info) {
  std::cout << "Population:\n"; 
  std::cout << "Chromosome" << std::setw(20) << "Fenotype"  << std::setw(18) << "Fitness" << "\n";
  for (int  i = 0; i < population_.size(); i++) {
    if (info == 1) {
      population_[i].printIndividual();
    }
    if (info == 2) {
      population_[i].printIndividual();
      std::cout << population_[i].getFenotype();
    }
    if (info == 3) {
      population_[i].printIndividual();
      std::cout << std::setw(20) << population_[i].getFenotype() << std::setw(20) << population_[i].getFitness();
    }
    printf("\n");
  }
}

void Population::crossover(void) {
  if (crossover_ == "two-point") {
    doTwoPoint();
  }
  if (crossover_ == "single-point") {
    doSinglePoint();
  }
}

void Population::selection(void) {
  selected_parents_.clear();
  if (selection_ == "roulette") {
    doRoulette();
  }
}

void Population::doTwoPoint(void) {
  std::vector<std::string> section = Split(crossover_section_, " ");
  std::vector<std::vector<Individual>> new_population;
  for (int i = 0; i < selected_parents_.size() / 2; i++) {
    new_population.push_back(selected_parents_[i].doTwoPoint(selected_parents_[i+1], std::stoi(section[0]), std::stoi(section[1])));
    i++;
  }
  for (int i = 0; i < new_population.size(); i++) {
    population_.push_back(new_population[i][0]);
    population_.push_back(new_population[i][1]);
  }
}

void Population::doSinglePoint(void) {
  std::vector<std::vector<Individual>> new_population;
  for (int i = 0; i < selected_parents_.size() / 2; i++) {
    new_population.push_back(selected_parents_[i].doSinglePoint(selected_parents_[i+1], std::stoi(crossover_section_)));
    i++;
  }
  for (int i = 0; i < new_population.size(); i++) {
    population_.push_back(new_population[i][0]);
    population_.push_back(new_population[i][1]);
  }
}

void Population::doRoulette(void) {
  std::vector<std::vector<float>> chance;
  std::vector<float> temp;
  for (int i = 0; i < population_.size(); i++) {
    temp.push_back(population_[i].getFitness() / total_fitness_);
    temp.push_back(i);
    chance.push_back(temp);
    temp.clear();
  }
  std::sort(chance.begin(), chance.end());
  std::reverse(chance.begin(), chance.end());
  for (int i = 1; i < chance.size(); i++) {
    chance[i][0] = chance[i][0] + chance[i-1][0] ;
  }
  for (int i = 0 ; i < population_.size() / 2 ; i++) {
    float random = (double) rand() / (RAND_MAX);
    for (int j = 0; j < chance.size(); j++) {
      if (random < chance[j][0]) {
        selected_parents_.push_back(population_[chance[j][1]]);
        chance.erase(chance.begin() + j);
        j = chance.size();
      }
    }
  }
}

void Population::translateFunction(void) {
  int *err;
  const char *expression = eval_function_.c_str();
  if (variable_.size() == 1) {
    te_variable vars[] = {"x", &x_};
    eval_fun_ = te_compile(expression, vars, 1, err);
  } else if (variable_.size() == 3) {
    te_variable vars[] = {{"x", &x_}, {"y", &y_}};
    eval_fun_ = te_compile(expression, vars, 2, err);
  } else if (variable_.size() == 5) {
    te_variable vars[] = {{"x", &x_}, {"y", &y_}, {"z", &z_}};
    eval_fun_ = te_compile(expression, vars, 3, err);
  }
}

std::string Population::Get_line(const std::string& filename, const int& line_number) {
  std::ifstream inputfile(filename);
  auto temp(1);
  std::string line;
  while( (!(inputfile.eof())) && (temp < line_number)) {
    std::getline(inputfile, line);
    ++temp;
  }
  std::getline(inputfile, line);
  return line;
}

std::vector<std::string> Population::Split (std::string str, std::string delim) {
  /// @brief this func split in 2 the string and store them in vector, 
  //         depending of the char
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) pos = str.length();
    std::string token = str.substr(prev, pos-prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  }
  while (pos < str.length() && prev < str.length());
  return tokens;
}

#endif