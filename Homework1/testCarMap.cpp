#include "CarMap.h"

int main(){
  
  CarMap mm;
  mm.addCar("test");
  std::cerr << mm.gas("test") << std::endl;
  mm.addGas("test", 14);
  std::cerr << mm.gas("test") << std::endl;
  std::cerr << "Fleet size: " << mm.fleetSize() << std::endl;
  mm.useGas("test", 10);
  std::cerr << mm.gas("test") << std::endl;
  std::cerr << "Fleet size: " << mm.fleetSize() << std::endl;

  mm.print();

  CarMap mn = mm;

  mn.print();

  CarMap me;
  me = mn;

  me.print();

}