#include "population.cpp"

#include <ctime>
#include "tinyexpr.h"



int main(void) {
  srand(time(NULL));
  Population a("../input/ebook.txt");
  printf("%f\n", te_interp("5*5", 0));
  return 0;
}