//#include "population.cpp"
#include "individual.cpp"
#include <ctime>


int main(void) {
  srand(time(NULL));
  Individual a(10,0,10,1);
  Individual b(10,0,10,1);
  a.printIndividual();
  b.printIndividual();
  std::vector<Individual> child = a.doOnePoint(b,3);
  child[0].printIndividual();
  child[1].printIndividual();
  //Population a("../input/hojadecalculo.txt");
  return 0;
}