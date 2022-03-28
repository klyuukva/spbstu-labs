#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iosfwd>
#include <string>
#include <list>

class Phonebook
{
public:
  struct Contact
  {
    std::string name;
    std::string phone;
  };

  using reference = typename std::list<Contact>::reference;
  using value_type = typename std::list<Contact>::value_type;
  using iterator = typename std::list<Contact>::iterator;
  using const_iterator = typename std::list<Contact>::const_iterator;

  void pushBack(const Contact& contact);
  void insert(const iterator& contactIterator, const Contact& contact);
  void erase(const iterator& contactIterator);
  iterator makeStep(iterator& iterator, int step);

  bool empty() const noexcept;
  size_t size() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

private:
  std::list<Contact> contactList_;
};

std::ostream& operator<<(std::ostream& out, const Phonebook::iterator& iterator);
std::istream& operator>>(std::istream& in, Phonebook::Contact& contact);

#endif
