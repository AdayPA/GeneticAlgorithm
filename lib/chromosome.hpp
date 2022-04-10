#ifndef CHROMOSOME_HPP_
#define CHROMOSOME_HPP_

#include <vector>

class Chromosome {

  public:

    Chromosome();
    Chromosome(int);
    ~Chromosome();
    inline const int getSize(void) { return size_; };
    bool getValue(int);
    void setChromosome(std::vector<bool>);
    
  private:
   
    std::vector<bool> gens_;
    int size_;
    void randomValue(int);

};

#endif