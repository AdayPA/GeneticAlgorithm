#include "../lib/population.hpp"

#include <exception>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

namespace {
void printUsage(const char* program) {
  std::cerr << "Usage: " << program << " [input-file] [--generations N] [--seed N]\n";
}

std::size_t parseSizeArg(const std::string& value, const std::string& name) {
  if (value.empty() || value[0] == '-') {
    throw std::invalid_argument("Invalid " + name + ": " + value);
  }

  std::size_t consumed = 0;
  const unsigned long result = std::stoul(value, &consumed);
  if (consumed != value.size()) {
    throw std::invalid_argument("Invalid " + name + ": " + value);
  }
  return static_cast<std::size_t>(result);
}
}

int main(int argc, char* argv[]) {
  std::string input_file = "../input/hojadecalculo.txt";
  std::size_t generations = 4;
  unsigned int seed = std::random_device{}();

  try {
    for (int i = 1; i < argc; i++) {
      const std::string argument = argv[i];
      if (argument == "-h" || argument == "--help") {
        printUsage(argv[0]);
        return 0;
      }
      if (argument == "--generations" || argument == "-g") {
        if (++i >= argc) {
          throw std::invalid_argument("Missing value for " + argument);
        }
        generations = parseSizeArg(argv[i], "generation count");
        continue;
      }
      if (argument == "--seed" || argument == "-s") {
        if (++i >= argc) {
          throw std::invalid_argument("Missing value for " + argument);
        }
        seed = static_cast<unsigned int>(parseSizeArg(argv[i], "seed"));
        continue;
      }
      input_file = argument;
    }

    Population population(input_file, seed);
    population.run(generations, std::cout);
  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << "\n";
    printUsage(argv[0]);
    return 1;
  }

  return 0;
}
