#include <iostream>
#include "MCsharem.hpp"

/**
 * @brief Fución principal.
 *
 * Crea un objeto de tipo MC y muestra: el volumen de una hiperesfera en 4D, cantidad de iteraciones y error cometido.
 */
int main(){

  MC MC1(10000000);
  MC1.calcInt();
  std::cout << MC1.getIntVal() << std::endl;
  std::cout << MC1.getNVal() << std::endl;
  std::cout << MC1.getErrVal() << std::endl;

  return 0;
}
