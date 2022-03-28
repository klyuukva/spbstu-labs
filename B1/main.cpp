#include <stdexcept>
#include <iostream>
#include <string>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2 || argc > 4)
  {
    std::cerr << "Invalid argument value.";
  }

  try
  {
    int argument = std::stoi(argv[1]);

    switch (argument)
    {
    case 1:
      if (argc != 3)
      {
        std::cerr << "Wrong count of arguments.";
        return 1;
      }

      command1(argv[2], std::cin, std::cout);
      break;
    case 2:
      if (argc != 3)
      {
        std::cerr << "Wrong count of arguments.";
        return 1;
      }

      command2(argv[2], std::cout);
      break;
    case 3:
      if (argc != 2)
      {
        std::cerr << "Wrong count of arguments.";
        return 1;
      }

      command3(std::cin, std::cout);
      break;
    case 4:
      if (argc != 4)
      {
        std::cerr << "Wrong count of arguments.";
        return 1;
      }

      command4(argv[2], std::stoi(argv[3]), std::cout);
      break;
    default:
      std::cerr << "Wrong input.";
      return 1;
    }
  }

  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 1;
  }
}
