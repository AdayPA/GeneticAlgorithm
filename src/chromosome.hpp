#ifndef CHROMOSOME_HPP_
#define CHROMOSOME_HPP_

#include <vector>

class Chromosome {

  public:

    Chromosome();
    Chromosome(int);
    ~Chromosome();
    
  private:
   
    std::vector<bool> gens_;
    void randomValue(int);

};

#endif