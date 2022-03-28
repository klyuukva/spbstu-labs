#include <stdexcept>
#include <iostream>
#include <string>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid argument value.";
    return 1;
  }

  try
  {
    int argument = std::stoi(argv[1]);
    switch (argument)
    {
    case 1:
      task1(std::cin, std::cout);
      break;

    case 2:
      task2(std::cin, std::cout);
      break;

    default:
      std::cerr << "Incorrect parameters.\n";
      return 1;
    }
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what();
    return 1;
  }
  return 0;
}
