#ifndef CHROMOSOME_HPP_
#define CHROMOSOME_HPP_

#include <vector>

class Chromosome {

  public:

    Chromosome(int);
    ~Chromosome();
    std::vector<bool> gens_;

  private:

    void randomValue(int &);

};


#endif