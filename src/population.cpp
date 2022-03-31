#ifndef POPULATION_CPP_
#define POPULATION_CPP_

#include "population.hpp"

#include <fstream>
#include <string>
#include <cmath>

Population::Population( std::string input_file) {
  population_size_ = std::stoi(Get_line(input_file,1));
  output_size_ = std::stoi(Get_line(input_file,2));
  variable_ = (Get_line(input_file,3));
  precision_ = std::stoi(Get_line(input_file,4));
  eval_function_ = Get_line(input_file,5);
  domain_func_ = Get_line(input_file,6);
  crossover_ = Get_line(input_file,7);
  selection_ = Get_line(input_file,8);
  std::vector<std::string> min_max = Split(domain_func_, " ");
  domain_ = std::stof(min_max[1]) - std::stof(min_max[0]);
  min_value = std::stof(min_max[0]);
  max_value = std::stof(min_max[1]);
  float chromosome_size = ceil(log2(domain_  * pow(10,precision_)));
  for (int i = 0; i < population_size_; i++) {
    population_.push_back(Individual(chromosome_size));
  }
  
  //doCycle();
  //translateFunction();
}

Population::~Population(){}

void Population::doCycle(void) {
  calcValue();
}

void Population::calcValue(void) {
  for (int i = 0; i < population_size_; i++) {
    population_values.push_back(population_[i].getValue());
  }
}

float Population::normalizeValue(int binary) {
  return 0.0;
}

void Population::translateFunction(void) {}

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