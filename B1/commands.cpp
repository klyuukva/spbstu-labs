#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include "commands.hpp"
#include "implementation.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

void command1(const char* sortMethod, std::istream& in, std::ostream& out)
{
  std::vector<int> vector;

  int element = 0;
  while (in >> element)
  {
    vector.push_back(element);
  }

  if (!in.eof())
  {
    throw std::invalid_argument("Read arguments are incorrect.");
  }

  std::vector<int> vectorAt = vector;
  std::list<int> list(vector.begin(), vector.end());

  std::function<bool(int, int)> method = getSortMethod<int>(sortMethod);

  sort<IndexItemAccess>(vector, method);
  sort<AtItemAccess>(vectorAt, method);
  sort<IteratorItemAccess>(list, method);

  print(vector, out);
  out << "\n";

  print(vectorAt, out);
  out << "\n";

  print(list, out);
  out << "\n";
}

void command2(const char* name, std::ostream& out)
{
  copyFile(name, out);
}

void command3(std::istream& in, std::ostream& out)
{
  std::vector<int> vector;

  int elm = 0;
  while (in >> elm)
  {
    if (elm == 0)
    {
      break;
    }
    vector.push_back(elm);
  }

  if (!in.eof() && in.fail())
  {
    throw std::invalid_argument("Wrong input. Incorrect data.");
  }

  if (elm != 0)
  {
    throw std::invalid_argument("Wrong input. Input must ends with zero.");
  }

  modifyVector(vector);

  print(vector, out);
  out << "\n";
}

void command4(const char* sortMethod, size_t size, std::ostream& out)
{
  std::vector<double> vector(size);
  fillRandom(&vector[0], size);

  print(vector, out);
  out << "\n";
  sortForRandomArray(vector, sortMethod);

  print(vector, out);
}
