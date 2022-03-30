#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "individual.cpp"

class Population {

  public:

    Population(std::string);
    ~Population();

  private:
  
  std::string Get_line (const std::string&, const int&);
  std::vector<Individual> population_;

};

#endif