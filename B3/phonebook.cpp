#include "phonebook.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "auxiliary-functions.hpp"

void Phonebook::pushBack(const Phonebook::Contact& contact)
{
  contactList_.push_back(contact);
}

void Phonebook::insert(const Phonebook::iterator& contactIterator, const Phonebook::Contact& contact)
{
  contactList_.insert(contactIterator, contact);
}

void Phonebook::erase(const Phonebook::iterator& contactIterator)
{
  contactList_.erase(contactIterator);
}

bool Phonebook::empty() const noexcept
{
  return contactList_.empty();
}

size_t Phonebook::size() const noexcept
{
  return contactList_.size();
}

Phonebook::iterator Phonebook::begin() noexcept
{
  return contactList_.begin();
}

Phonebook::iterator Phonebook::end() noexcept
{
  return contactList_.end();
}

Phonebook::const_iterator Phonebook::cbegin() const noexcept
{
  return contactList_.cbegin();
}

Phonebook::const_iterator Phonebook::cend() const noexcept
{
  return contactList_.begin();
}

Phonebook::iterator Phonebook::makeStep(Phonebook::iterator& iterator, int step)
{
  if (step == 0)
  {
    throw std::invalid_argument("Step cannot be zero.");
  }

  if (step > 0)
  {
    while (std::next(iterator) != contactList_.end() && step > 0)
    {
      iterator = std::next(iterator);
      step--;
    }
  }
  else
  {
    while (std::next(iterator) != contactList_.begin() && step < 0)
    {
      iterator = std::prev(iterator);
      step++;
    }
  }
  return iterator;
}

std::ostream& operator<<(std::ostream& out, const Phonebook::iterator& iterator)
{
  out << iterator->phone << " " << iterator->name;
  return out;
}

std::istream& operator>>(std::istream& in, Phonebook::Contact& contact)
{
  std::string phone;
  in >> skipSpacesExcludingNewline >> std::noskipws >> phone;

  if (phone.empty())
  {
    in.setstate(std::ios_base::failbit);
  }

  if (!std::all_of(phone.begin(), phone.end(), [](auto& digit)
  {
    return std::isdigit(digit);
  }))
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios_base::failbit);
    return in;
  }

  char element = ' ';

  std::string name;
  in >> skipSpacesExcludingNewline;

  if (in.get() != '\"')
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios_base::failbit);
    return in;
  }

  element = in.get();
  std::ios_base::iostate inState = in.rdstate();

  while (element != '\n' && !in.eof())
  {
    if (element == '\\')
    {
      element = in.get();
      if (element != '\\' && element != '\"')
      {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in.setstate(std::ios_base::failbit);
        return in;
      }
    }
    else if (element == '\"')
    {
      element = in.get();

      if (element != '\r')
      {
        if (element != '\n' && !in.eof())
        {
          in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          in.setstate(std::ios_base::failbit);
          return in;
        }
      }
      if (in.eof())
      {
        in.clear();
        in.setstate(inState);
      }
      break;
    }
    name += element;

    element = in.get();
  }

  if (name.empty())
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios_base::failbit);
    return in;
  }

  contact.name = name;
  contact.phone = phone;

  return in;
}
