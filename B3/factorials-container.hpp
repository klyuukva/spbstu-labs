#ifndef FACTORIALS_CONTAINER_HPP
#define FACTORIALS_CONTAINER_HPP

#include <iterator>

class FactorialsContainer
{
public:
  class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, unsigned int, unsigned int, const unsigned int*, unsigned int>
  {
  public:

    friend class FactorialsContainer;

    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    const size_t& operator*();

    bool operator==(const Iterator& rhs) const;
    bool operator!=(const Iterator& rhs) const;

  private:
    Iterator(size_t index, size_t value);
    size_t index_;
    size_t value_;
  };

  FactorialsContainer(size_t min, size_t max);
  Iterator begin() const;
  Iterator end() const;

private:
  size_t minValueIterator_;
  size_t maxValueIterator_;
  size_t minIndex_;
  size_t maxIndex_;
};

#endif
