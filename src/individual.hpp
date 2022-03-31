#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "chromosome.cpp"
class Individual {

  public:

    Individual();
    Individual(int, float, float, int);
    ~Individual();
    inline int getValue(void) { return chromosome_value_; };
    inline float getFenotype(void) { return fenotype_; };
    inline float getFitness(void) { return fitness_; };
    inline void setFitness(float fitness) { fitness_ = fitness; };

  private:
    void calcFenotype(void);
    void normalize(void);
    Chromosome chromosome_;
    float fenotype_;
    float fitness_;
    int chromosome_value_;
    float min_value_;
    float max_value_;
    int precision_;

};

#endif