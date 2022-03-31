#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "chromosome.cpp"
class Individual {

  public:

    Individual();
    Individual(int, float, float);
    ~Individual();
    inline int getValue(void) { return chromosome_value_; };
    inline float getFenotype(void) { return fenotype_; };

  private:
    void calcFenotype(void);
    void normalize(void);
    Chromosome chromosome_;
    float fenotype_;
    int chromosome_value_;
    float min_value_;
    float max_value_;

};

#endif