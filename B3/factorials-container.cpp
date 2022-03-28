#include "factorials-container.hpp"

static size_t getFactorial(size_t index);

FactorialsContainer::FactorialsContainer(size_t min, size_t max) :
  minValueIterator_(getFactorial(min)),
  maxValueIterator_(getFactorial(max + 1)),
  minIndex_(min),
  maxIndex_(max + 1)
{ }

FactorialsContainer::Iterator FactorialsContainer::begin() const
{
  return FactorialsContainer::Iterator(minIndex_, minValueIterator_);
}

FactorialsContainer::Iterator FactorialsContainer::end() const
{
  return FactorialsContainer::Iterator(maxIndex_, maxValueIterator_);
}

size_t getFactorial(size_t index)
{
  size_t temp = 1;
  for (size_t i = 1; i <= index; i++)
  {
    temp *= i;
  }
  return temp;
}

