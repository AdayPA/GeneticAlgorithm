#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "../src/individual.cpp"
#include "tinyexpr.h"
class Population {

  public:

    Population(std::string);
    ~Population();

  private:
  
  std::string Get_line (const std::string&, const int&);
  std::vector<std::string> Split (std::string, std::string);
  void printPopulation(int);
  void printSelectedParent();
  void doCycle(void);
  void translateFunction(void);
  void calcFitness(void);
  void selection(void);
  void crossover(void);
  void doRoulette(void);
  void doTwoPoint(void);
  void doSinglePoint(void);
  std::vector<Individual> population_;
  std::vector<Individual> selected_parents_;
  float min_value_;
  float max_value_;
  float domain_;
  float total_fitness_;
  double x_;
  double y_;
  double z_;
  int population_size_;
  int output_size_;
  int precision_;
  int chromosome_size_;
  std::string variable_;
  std::string eval_function_;
  std::string domain_func_;
  std::string crossover_;
  std::string selection_;
  std::string crossover_section_;

  te_expr *eval_fun_;
  
};

#endif