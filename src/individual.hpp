#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "chromosome.cpp"
class Individual {

  public:

    Individual(int);
    ~Individual();
    int getValue(void);

  private:

    Chromosome chromosome_;

};

#endif