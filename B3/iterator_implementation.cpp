#include "factorials-container.hpp"

FactorialsContainer::Iterator::Iterator(size_t index, size_t value) :
  index_(index),
  value_(value)
{ }

FactorialsContainer::Iterator& FactorialsContainer::Iterator::operator++()
{
  value_ *= ++index_;
  return *this;
}

FactorialsContainer::Iterator& FactorialsContainer::Iterator::operator--()
{
  value_ /= index_--;
  return *this;
}

FactorialsContainer::Iterator FactorialsContainer::Iterator::operator++(int)
{
  Iterator iterator = *this;
  iterator++;
  return iterator;
}

FactorialsContainer::Iterator FactorialsContainer::Iterator::operator--(int)
{
  Iterator iterator = *this;
  --iterator;
  return iterator;
}

const size_t& FactorialsContainer::Iterator::operator*()
{
  return value_;
}

bool FactorialsContainer::Iterator::operator==(const Iterator& rhs) const
{
  return index_ == rhs.index_;
}

bool FactorialsContainer::Iterator::operator!=(const Iterator& rhs) const
{
  return !(*this == rhs);
}
