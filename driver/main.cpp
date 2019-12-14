#include "bc_driver.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
  std::string buf;

  while(buf != "q"){
    std::cout << "<backward> -100 ... 100 <forward>" << std::endl;
    std::cout << "q: quit" << std::endl;
    std::cout << "?>" << std::endl;
    std::cin >> buf;
    const int value = std::atoi(argv[1]);
    bc::control_motor(value);
  }
  return 0;
}