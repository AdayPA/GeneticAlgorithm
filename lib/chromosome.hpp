#ifndef CHROMOSOME_HPP_
#define CHROMOSOME_HPP_

#include <vector>

class Chromosome {

  public:

    Chromosome();
    Chromosome(int);
    ~Chromosome();
    int getSize(void);
    bool getValue(int);
    void setChromosome(std::vector<bool>);
    
  private:
   
    std::vector<bool> gens_;
    int size_;
    void randomValue(int);

};

#endif