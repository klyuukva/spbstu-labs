#include "tasks.hpp"

#include <iostream>
#include <stdexcept>

#include "bookmarks.hpp"
#include "commands.hpp"

void task1(std::istream& in, std::ostream& out)
{
  Bookmarks bookmarks;

  while (in >> std::ws && !in.eof())
  {
    functionBookmark function;
    in >> function;

    if (in.fail())
    {
      throw std::ios_base::failure("Couldn't read file or wrong input.");
    }

    function(bookmarks, out);
  }

  if (!in.eof())
  {
    throw std::ios_base::failure("Couldn't read file or wrong input.");
  }
}
