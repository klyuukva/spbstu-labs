#ifndef BOOKMARKS_HPP
#define BOOKMARKS_HPP

#include <string>
#include <map>
#include <iostream>

#include "phonebook.hpp"

class Bookmarks
{
public:
  enum Position
  {
    FIRST,
    LAST
  };

  enum InsertPosition
  {
    AFTER,
    BEFORE
  };

  Bookmarks();

  void add(const Phonebook::Contact& contact);
  void store(const std::string& name, const std::string& newName);
  void insert(InsertPosition insertPosition, const std::string& name, const Phonebook::Contact& contact);
  void deleteMark(const std::string& name);
  void show(std::ostream& out, const std::string& name) const;
  void move(const std::string& name, Position& position);
  void move(const std::string& name, int steps);

  bool empty() const;

private:
  Phonebook phonebook_;
  std::map<std::string, Phonebook::iterator> bookmarks_;
};

#endif
