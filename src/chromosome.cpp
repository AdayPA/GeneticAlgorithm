#ifndef CHROMOSOME_CPP_
#define CHROMOSOME_CPP_

#include "chromosome.hpp"

#include <iostream>


Chromosome::Chromosome(){}

Chromosome::Chromosome(int size) {
  randomValue(size);
}

Chromosome::~Chromosome() {
}

void Chromosome::randomValue(int size) {
  for (int i = 0; i < size; i++) {
    gens_.push_back(rand() > (RAND_MAX / 2));
    std::cout << gens_[i];
  }
  std::cout << "\n";
}

#endif