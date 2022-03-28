#include <iostream>
#include <stdexcept>
#include <list>

#include "tasks.hpp"

void task2(std::istream& in, std::ostream& out)
{
  static const int MAX_SIZE_OF_ELEMENTS = 20;
  static const int MIN_SIZE_OF_ELEMENTS = 1;
  static const int MAX_SIZE_OF_RANGE = 20;

  std::list<int> queue;
  int element = 0;

  while (in >> element && !in.eof())
  {

    if ((element < MIN_SIZE_OF_ELEMENTS) || (element > MAX_SIZE_OF_ELEMENTS))
    {
      throw std::invalid_argument("The range of values can be between 1 and 20.");
    }

    queue.push_back(element);
  }

  if (!in.eof())
  {
    throw std::ios_base::failure("Couldn't read file.");
  }

  if (queue.size() >= MAX_SIZE_OF_RANGE + 1)
  {
    throw std::out_of_range("Queue size cannot exceed 20.");
  }

  if (queue.empty())
  {
    return;
  }

  for (auto front = queue.begin(), end = queue.end(); front != end--; front++)
  {
    if (front == end)
    {
      out << *front;
      break;
    }
    out << *front << " " << *end << " ";
  }
  std::cout << "\n";
}
