#ifndef INDIVIDUAL_CPP_
#define INDIVIDUAL_CPP_

#include "individual.hpp"

#include <cmath>

Individual::Individual(int size, float min_value, float max_value){
  chromosome_ = Chromosome(size);
  chromosome_value_ = 0;
  fenotype_ = 0.0;
  min_value_ = min_value;
  max_value_ = max_value;
  calcFenotype();
  normalize();
}

Individual::~Individual(){}

void Individual::calcFenotype(void) {
  for (int i = 0; i <chromosome_.getSize()  ; i++) {
    chromosome_value_ += chromosome_.getValue(i) * pow(2,(chromosome_.getSize() - 1)- i);
  }
}

void Individual::normalize(void) {
  fenotype_ = min_value_ + (chromosome_value_ * (3 / ( pow(2,chromosome_.getSize()) - 1)));
}

#endif