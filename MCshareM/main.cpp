#include <iostream>
#include "MCsharem.hpp"

int main(){

  MC MC1(10000000);
  MC1.calcInt();
  std::cout << MC1.getIntVal() << std::endl;
  std::cout << MC1.getNVal() << std::endl;
  std::cout << MC1.getErrVal() << std::endl;

  return 0;
}
