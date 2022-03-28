#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>

void command1(const char* sortMethod, std::istream& in, std::ostream& out);
void command2(const char* name, std::ostream& out);
void command3(std::istream& in, std::ostream& out);
void command4(const char* sortMethod, std::size_t size, std::ostream& out);

template<typename T>
void print(const T& container, std::ostream& out)
{
  for (auto i:container)
  {
    out << i << " ";
  }
}

#endif
