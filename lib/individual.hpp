#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "chromosome.hpp"

#include <iosfwd>
#include <random>
#include <vector>

class Individual {

  public:

    Individual();
    Individual(Chromosome, double, double, int);
    Individual(std::size_t, double, double, int, std::mt19937&);
    ~Individual();
    unsigned long long getValue(void) const;
    std::size_t getSize(void) const;
    int getPrecision(void) const;
    double getMinValue(void) const;
    double getMaxValue(void) const;
    double getFenotype(void) const;
    double getFitness(void) const;
    void setFitness(double);
    bool getGen(std::size_t) const;
    void printIndividual(std::ostream&) const;
    std::vector<Individual> doSinglePoint(const Individual&, std::size_t) const;
    std::vector<Individual> doTwoPoint(const Individual&, std::size_t, std::size_t) const;

  private:
  
    void calcFenotype(void);
    void normalize(void);
    Chromosome chromosome_;
    double fenotype_;
    double fitness_;
    double min_value_;
    double max_value_;
    unsigned long long chromosome_value_;
    int precision_;
};

#endif
