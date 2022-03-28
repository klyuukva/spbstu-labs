#include "tasks.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

#include "factorials-container.hpp"

void task2(std::ostream& out)
{
  FactorialsContainer container(1, 10);

  std::copy(container.begin(), container.end(), std::ostream_iterator<unsigned>(out, " "));
  out << "\n";

  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<unsigned>(out, " "));
  out << "\n";
}
