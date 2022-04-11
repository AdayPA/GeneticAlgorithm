#include "../lib/chromosome.hpp"

#include <utility>

Chromosome::Chromosome(){}

Chromosome::Chromosome(std::size_t size, std::mt19937& rng) {
  randomValue(size, rng);
}

Chromosome::Chromosome(std::vector<bool> gens)
    : gens_(std::move(gens)) {}

Chromosome::~Chromosome() {}

void Chromosome::randomValue(std::size_t size, std::mt19937& rng) {
  std::bernoulli_distribution coin(0.5);
  gens_.reserve(size);
  for (std::size_t i = 0; i < size; i++) {
    gens_.push_back(coin(rng));
  }
}

std::size_t Chromosome::getSize(void) const {
  return gens_.size();
}

bool Chromosome::getValue(std::size_t pos) const {
  return gens_.at(pos);
}

const std::vector<bool>& Chromosome::getGenes(void) const {
  return gens_;
}
