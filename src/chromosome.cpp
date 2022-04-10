#ifndef CHROMOSOME_CPP_
#define CHROMOSOME_CPP_

#include "../lib/chromosome.hpp"

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
  }
}

void Chromosome::setChromosome(std::vector<bool> gens) {
  gens_ = gens;
}

bool Chromosome::getValue(int pos) {
  return gens_.at(pos);
}

#endif