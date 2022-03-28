#include "commands.hpp"

#include <stdexcept>
#include <iostream>

#include "auxiliary-functions.hpp"

functionBookmark parseAdd(std::istream& in)
{
  Phonebook::Contact contact;

  in >> contact;

  if (in.fail())
  {
    in.clear();
    return outputErrorMessage;
  }

  return [contact](Bookmarks& phonebook, std::ostream&)
  {
    phonebook.add(contact);
  };

}

functionBookmark parseStore(std::istream& in)
{
  std::string oldName;
  if (!parseMarkName(oldName, in))
  {
    return outputErrorMessage;
  }

  std::string newName;
  if (!parseMarkName(newName, in))
  {
    return outputErrorMessage;
  }

  return [oldName, newName](Bookmarks& phonebook, std::ostream&)
  {
    phonebook.store(oldName, newName);
  };
}

functionBookmark parseInsert(std::istream& in)
{
  std::string insertPosition;

  in >> skipSpacesExcludingNewline >> std::noskipws >> insertPosition;

  if (in.fail())
  {
    in.clear();
    return outputErrorMessage;
  }
  std::string tempMarkName;

  if (!parseMarkName(tempMarkName, in))
  {
    return outputErrorMessage;
  }

  Phonebook::Contact contact;

  in >> contact;

  if (in.fail())
  {
    in.clear();
    return outputErrorMessage;
  }

  return [insertPosition, contact, tempMarkName](Bookmarks& phonebook, std::ostream& out)
  {
    if (insertPosition == "before")
    {
      phonebook.insert(Bookmarks::BEFORE, tempMarkName, contact);
    }
    else if (insertPosition == "after")
    {
      phonebook.insert(Bookmarks::AFTER, tempMarkName, contact);
    }
    else
    {
      return outputErrorMessage(phonebook, out);
    }
  };
}

functionBookmark parseDeleteMark(std::istream& in)
{
  std::string mark;

  if (!parseMarkName(mark, in))
  {
    return outputErrorMessage;
  }
  return [mark](Bookmarks& phonebook, std::ostream&)
  {
    phonebook.deleteMark(mark);
  };
}

functionBookmark parseShow(std::istream& in)
{
  std::string mark;

  if (!parseMarkName(mark, in))
  {
    return outputErrorMessage;
  }
  return [mark](Bookmarks& phonebook, std::ostream& out)
  {
    phonebook.show(out, mark);
  };
}

functionBookmark parseMove(std::istream& in)
{
  std::string mark;

  if (!parseMarkName(mark, in))
  {
    return outputErrorMessage;
  }

  std::string steps;
  in >> skipSpacesExcludingNewline >> steps;

  return [mark, steps](Bookmarks& phonebook, std::ostream& out)
  {
    if (steps == "first")
    {
      Bookmarks::Position posFirst = Bookmarks::Position::FIRST;
      phonebook.move(mark, posFirst);
      return;
    }
    if (steps == "last")
    {
      Bookmarks::Position posLast = Bookmarks::Position::LAST;
      phonebook.move(mark, posLast);
      return;
    }
    if (steps.at(0) == '+' || steps.at(0) == '-')
    {
      std::string tempSteps = steps.substr(1, steps.size() - 1);
      if (!checkNumber(tempSteps))
      {
        outputErrorMessageForSteps(phonebook, out);
        return;
      }
      phonebook.move(mark, std::stoi(steps));
    }
    else
    {
      if (!checkNumber(steps))
      {
        outputErrorMessageForSteps(phonebook, out);
        return;
      }
      phonebook.move(mark, std::stoi(steps));
    }

  };
}

bool parseMarkName(std::string& name, std::istream& in)
{
  bool flag = false;
  std::string tempStr;

  in >> skipSpacesExcludingNewline >> tempStr;

  for (auto& element: tempStr)
  {
    if (std::isalnum(element) && element != '-')
    {
      flag = true;
    }
  }
  name = tempStr;
  return flag;
}

bool checkNumber(const std::string& number)
{
  if (number.empty())
  {
    return false;
  }
  for (char i: number)
  {
    if (!std::isdigit(i))
    {
      return false;
    }
  }
  return true;
}

void outputErrorMessage(Bookmarks&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

void outputErrorMessageForSteps(Bookmarks&, std::ostream& out)
{
  out << "<INVALID STEP>\n";
}

std::istream& operator>>(std::istream& in, functionBookmark& functionBookmark)
{
  static const std::map<std::string, functionMap> functions =
    {
      {"add",    parseAdd},
      {"store",  parseStore},
      {"insert", parseInsert},
      {"delete", parseDeleteMark},
      {"show",   parseShow},
      {"move",   parseMove},
    };

  std::string command;
  in >> std::ws >> command;

  if (in.fail())
  {
    return in;
  }

  auto iterator = functions.find(command);
  if (iterator != functions.end())
  {
    functionBookmark = iterator->second(in);
  }
  else
  {
    functionBookmark = outputErrorMessage;
  }
  return in;
}
