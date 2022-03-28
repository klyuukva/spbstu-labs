#include "auxiliary-functions.hpp"

#include <istream>
#include <cctype>

std::istream& skipSpacesExcludingNewline(std::istream& in)
{
  for (char i = in.get(); isspace(i) && i != '\n'; i = in.get())
  { }

  if (!in.eof())
  {
    in.unget();
  }

  return in;
}
