#ifndef INDIVIDUAL_CPP_
#define INDIVIDUAL_CPP_

#include "../lib/individual.hpp"

#include <cmath>

Individual::Individual(int size, float min_value, float max_value, int precision) {
  chromosome_ = Chromosome(size);
  chromosome_value_ = 0;
  fenotype_ = 0.0;
  fitness_ = 0.0;
  min_value_ = min_value;
  max_value_ = max_value;
  precision_ = precision;
  size_ = size;
  calcFenotype();
  normalize();
}

Individual::Individual(Chromosome chromosome, int size, float min_value, float max_value, int precision) {
  chromosome_ = chromosome;
  chromosome_value_ = 0;
  fenotype_ = 0.0;
  fitness_ = 0.0;
  min_value_ = min_value;
  max_value_ = max_value;
  precision_ = precision;
  size_ = size;
  calcFenotype();
  normalize();
}

Individual::~Individual() {}

std::vector<Individual> Individual::doSinglePoint(Individual p1, int section) {
  std::vector<bool> offspring1;
  std::vector<bool> offspring2;
  #pragma unroll
  for (int i = 0; i < section; i++) {
    offspring1.push_back(p1.getGen(i));
    offspring2.push_back(this->getGen(i));
  }
  #pragma unroll
  for (int i = section; i < p1.size_; i++) {
    offspring1.push_back(this->getGen(i));
    offspring2.push_back( p1.getGen(i));
  }
  std::vector<Individual> result;
  Chromosome child1(size_);
  child1.setChromosome(offspring1);
  Individual c1(child1, p1.getSize(), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  result.push_back(c1);
  Chromosome child2(size_);
  child2.setChromosome(offspring2);
  Individual c2(child2, p1.getSize(), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  result.push_back(c2);
  return result;
}

std::vector<Individual> Individual::doTwoPoint( Individual p1, int first, int second) {
  std::vector<bool> offspring1;
  std::vector<bool> offspring2;
  for (int i = 0; i < first; i++) {
    offspring1.push_back(this->getGen(i));
    offspring2.push_back(p1.getGen(i));
  }
  for (int i = first; i < second; i++) {
    offspring1.push_back(p1.getGen(i));
    offspring2.push_back(this->getGen(i));
  }
  for (int i = second; i < size_; i++) {
    offspring1.push_back(this->getGen(i));
    offspring2.push_back(p1.getGen(i));
  }
  std::vector<Individual> result;
  Chromosome child1(size_);
  child1.setChromosome(offspring1);
  Individual c1(child1, p1.getSize(), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  result.push_back(c1);
  Chromosome child2(size_);
  child2.setChromosome(offspring2);
  Individual c2(child2, p1.getSize(), p1.getMinValue(), p1.getMaxValue(), p1.getPrecision());
  result.push_back(c2);
  return result;
}

bool Individual::getGen(int pos) {
  return chromosome_.getValue(pos);
}

void Individual::calcFenotype(void) {
  for (int i = 0; i <chromosome_.getSize()  ; i++) {
    chromosome_value_ += chromosome_.getValue(i) * pow(2,(chromosome_.getSize() - 1)- i);
  }
}

void Individual::normalize(void) {
  if (precision_ == 1) {
    fenotype_ = chromosome_value_;
  } else {
    fenotype_ = min_value_ + (chromosome_value_ * (3 / ( pow(2,chromosome_.getSize()) - 1)));
  }
}

void Individual::printIndividual(void) {
  for (int i = 0; i < chromosome_.getSize(); i++) {
    std::cout << chromosome_.getValue(i);
  }
}


#endif