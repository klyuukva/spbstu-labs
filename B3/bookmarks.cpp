#include "bookmarks.hpp"

#include <iostream>
#include <string>
#include <algorithm>

Bookmarks::Bookmarks()
{
  bookmarks_["current"] = phonebook_.begin();
}

void Bookmarks::add(const Phonebook::Contact& contact)
{
  phonebook_.pushBack(contact);

  if (phonebook_.size() == 1)
  {
    std::for_each(bookmarks_.begin(), bookmarks_.end(), [&](auto& it)
    {
      it.second = phonebook_.begin();
    });
  }
}

void Bookmarks::store(const std::string& name, const std::string& newName)
{
  auto iterator = bookmarks_.find(name);
  if (iterator != bookmarks_.end())
  {
    bookmarks_.emplace(newName, iterator->second);
  }
  else
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
}

void Bookmarks::insert(Bookmarks::InsertPosition insertPosition,
                       const std::string& name, const Phonebook::Contact& contact)
{
  auto iterator = bookmarks_.find(name);
  if (iterator != bookmarks_.end())
  {
    if (iterator->second == phonebook_.end())
    {
      add(contact);
    }
    if (insertPosition == InsertPosition::BEFORE)
    {
      phonebook_.insert(iterator->second, contact);
    }
    if (insertPosition == InsertPosition::AFTER)
    {
      phonebook_.insert(std::next(iterator->second), contact);
    }
  }
  else
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
}

void Bookmarks::deleteMark(const std::string& name)
{
  auto iterator = bookmarks_.find(name);

  if (iterator != bookmarks_.end())
  {
    auto deleteIterator = iterator->second;
    auto bookmarkIterator = bookmarks_.begin();

    while (bookmarkIterator != bookmarks_.end())
    {
      if (bookmarkIterator->second == deleteIterator)
      {
        if (std::next(bookmarkIterator->second) != phonebook_.end())
        {
          bookmarkIterator->second = std::next(deleteIterator);
        }
        else
        {
          bookmarkIterator->second = std::prev(deleteIterator);
        }
      }

      bookmarkIterator++;
    }
    phonebook_.erase(deleteIterator);
  }
  else
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
  return;
}

void Bookmarks::show(std::ostream& out, const std::string& name) const
{
  auto iterator = bookmarks_.find(name);

  if (iterator != bookmarks_.end())
  {
    if (phonebook_.empty())
    {
      out << "<EMPTY>\n";
      return;
    }
    out << iterator->second << "\n";
    return;
  }
  out << "<INVALID BOOKMARK>\n";
}

void Bookmarks::move(const std::string& name, Position& position)
{
  auto iterator = bookmarks_.find(name);
  if (iterator != bookmarks_.end())
  {
    if (position == Position::FIRST)
    {
      iterator->second = phonebook_.begin();
    }
    if (position == Position::LAST)
    {
      iterator->second = --phonebook_.end();
    }
  }
  else
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
}

void Bookmarks::move(const std::string& name, int steps)
{
  auto iterator = bookmarks_.find(name);
  if (iterator != bookmarks_.end())
  {
    iterator->second = phonebook_.makeStep(iterator->second, steps);
  }
  else
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
}

bool Bookmarks::empty() const
{
  return phonebook_.empty();
}
