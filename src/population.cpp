#ifndef POPULATION_CPP_
#define POPULATION_CPP_

#include "population.hpp"

#include <fstream>
#include <string>

Population::Population( std::string input_file) {
  int population = std::stoi(Get_line(input_file,1));
  int output_size = std::stoi(Get_line(input_file,2));
  std::string variable = (Get_line(input_file,3));
  int precision = std::stoi(Get_line(input_file,4));
  std::string eval_function = Get_line(input_file,5);
  std::string domain_func = Get_line(input_file,6);
  std::string crossover = Get_line(input_file,7);


  for (int i = 0; i < population; i++) {
    population_.push_back(Individual(2));
  }


}

Population::~Population(){}

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

#endif