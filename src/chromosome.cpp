#ifndef CHROMOSOME_CPP_
#define CHROMOSOME_CPP_

#include "chromosome.hpp"

#include <iostream>


Chromosome::Chromosome(){}

Chromosome::Chromosome(int size) {
  randomValue(size);
  size_ = size;
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

int Chromosome::getSize(void) {
  return size_;
}

bool Chromosome::getValue(int pos) {
  return gens_.at(pos);
}

#endif