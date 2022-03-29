#ifndef CHROMOSOME_CPP_
#define CHROMOSOME_CPP_

#include "chromosome.hpp"

#include <iostream>
#include <time.h>

Chromosome::Chromosome(int size) {
  gens_.resize(size);
  randomValue(size);
}

Chromosome::~Chromosome() {
}

void Chromosome::randomValue(int &size) {
  srand (time(NULL));
  for (int i = 0; i < size; i++) {
    gens_[i] = rand() > (RAND_MAX / 2);
    std::cout << gens_[i];
  }
}

#endif