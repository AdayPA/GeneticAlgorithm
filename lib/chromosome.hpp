#ifndef CHROMOSOME_HPP_
#define CHROMOSOME_HPP_

#include <cstddef>
#include <random>
#include <vector>

class Chromosome {

  public:

    Chromosome();
    explicit Chromosome(std::size_t, std::mt19937&);
    explicit Chromosome(std::vector<bool>);
    ~Chromosome();
    std::size_t getSize(void) const;
    bool getValue(std::size_t) const;
    const std::vector<bool>& getGenes(void) const;
    
  private:
   
    std::vector<bool> gens_;
    void randomValue(std::size_t, std::mt19937&);

};

#endif
