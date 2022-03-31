#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "individual.cpp"

class Population {

  public:

    Population(std::string);
    ~Population();

  private:
  
  std::string Get_line (const std::string&, const int&);
  std::vector<std::string> Split (std::string, std::string);
  float normalizeValue(int);
  void doCycle(void);
  void calcValue(void);
  void translateFunction(void);
  std::vector<Individual> population_;
  std::vector<int> population_values;
  float min_value;
  float max_value;
  float domain_;
  int population_size_;
  int output_size_;
  int precision_;
  std::string variable_;
  std::string eval_function_;
  std::string domain_func_;
  std::string crossover_;
  std::string selection_;
  
};

#endif