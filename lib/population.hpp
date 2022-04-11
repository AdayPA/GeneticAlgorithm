#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "individual.hpp"
#include "tinyexpr.h"

#include <iosfwd>
#include <random>
#include <string>
#include <vector>

class Population {

  public:

    explicit Population(const std::string&, unsigned int);
    ~Population();
    void run(std::size_t, std::ostream&);

  private:
  enum class CrossoverType {
    SinglePoint,
    TwoPoint
  };

  enum class SelectionType {
    Roulette
  };

  struct Config {
    std::size_t population_size;
    std::size_t variable_count;
    std::string variable;
    int precision;
    std::string fitness_function;
    double min_value;
    double max_value;
    CrossoverType crossover_type;
    SelectionType selection_type;
    std::vector<std::size_t> crossover_points;
  };

  Config loadConfig(const std::string&) const;
  void validateConfig(void) const;
  std::vector<std::string> split(const std::string&) const;
  void printPopulation(std::ostream&, const std::string&) const;
  void getNextGeneration(void);
  void doCycle(void);
  void translateFunction(void);
  void calcFitness(void);
  void selection(void);
  void crossover(void);
  std::vector<Individual> doRoulette(const std::vector<Individual>&, std::size_t);
  void doTwoPoint(void);
  void doSinglePoint(void);
  double rouletteWeightFloor(const std::vector<Individual>&) const;

  Config config_;
  std::vector<Individual> population_;
  std::vector<Individual> selected_parents_;
  std::mt19937 rng_;
  double x_;
  std::size_t chromosome_size_;

  te_expr *eval_fun_;
  
};

#endif
