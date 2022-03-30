#ifndef INDIVIDUAL_CPP_
#define INDIVIDUAL_CPP_

#include "individual.hpp"

Individual::Individual(int size){
  chromosome_ = Chromosome(size);
}

Individual::~Individual(){}

#endif