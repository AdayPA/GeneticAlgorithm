#ifndef INDIVIDUAL_CPP_
#define INDIVIDUAL_CPP_

#include "individual.hpp"

#include <cmath>

Individual::Individual(int size){
  chromosome_ = Chromosome(size);
}

Individual::~Individual(){}

int Individual::getValue(void) {
  int sum = 0;
  for (int i = 0; i <chromosome_.getSize()  ; i++) {
    sum += chromosome_.getValue(i) * pow(2,(chromosome_.getSize() - 1)- i);
  }
  return sum;
}

#endif