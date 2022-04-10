#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "../src/chromosome.cpp"
class Individual {

  public:

    Individual();
    Individual(Chromosome);
    Individual(int, float, float, int);
    ~Individual();
    inline int getValue(void) { return chromosome_value_; };
    inline int getSize(void) { return size_; };
    inline float getFenotype(void) { return fenotype_; };
    inline float getFitness(void) { return fitness_; };
    inline void setFitness(float fitness) { fitness_ = fitness; };
    bool getGen(int);
    void printIndividual(void);
    std::vector<Individual> doOnePoint(const Individual, int);

  private:
  
    void calcFenotype(void);
    void normalize(void);
    Chromosome chromosome_;
    float fenotype_;
    float fitness_;
    float min_value_;
    float max_value_;
    int chromosome_value_;
    int precision_;
    int size_;
};

#endif