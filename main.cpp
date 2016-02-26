#include "micpower.hpp"

#include <iostream>       // std::cout, std::endl
 
int main() 
{
  micpower pwr;
  
  std::cout << "countdown:\n";
   
   pwr.start();

  for (int i=5; i>0; --i) {

    std::cout << i << std::endl;
    sleep(1);
  }
  std::cout << "Lift off!\n";

    pwr.stop();
    
    for (int i=5; i>0; --i) {

    std::cout << i << std::endl;
    sleep(1);
  }
  std::cout << "Lift off!\n";
  
  pwr.start();

  for (int i=5; i>0; --i) {

    std::cout << i << std::endl;
    sleep(1);
  }
  std::cout << "Lift off!\n";

    pwr.stop();
  return 0;
}