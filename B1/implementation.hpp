#ifndef TASK1_HPP
#define TASK1_HPP

#include <vector>
#include <stdexcept>
#include <functional>
#include <cstring>

template<typename T>
std::function<bool(const T&, const T&)> getSortMethod(const char* method);

template<typename T>
std::function<bool(const T&, const T&)> getSortMethod(const char* method)
{
  if (strcmp(method, "ascending") == 0)
  {
    return std::greater<T>();
  }
  else if (strcmp(method, "descending") == 0)
  {
    return std::less<T>();
  }
  else
  {
    throw std::invalid_argument("Wrong method name.");
  }
}

template<typename Container>
class IndexItemAccess
{
public:
  using iterator = std::size_t;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using value_type = typename Container::value_type;

  static iterator begin(const Container&);
  static iterator end(const Container& container);
  static reference access(Container& container, iterator number);
};

template<typename Container>
typename IndexItemAccess<Container>::iterator IndexItemAccess<Container>::begin(const Container&)
{
  return 0;
}

template<typename Container>
typename IndexItemAccess<Container>::iterator IndexItemAccess<Container>::end(const Container& container)
{
  return container.size();
}

template<typename Container>
typename IndexItemAccess<Container>::reference
IndexItemAccess<Container>::access(Container& container, IndexItemAccess::iterator number)
{
  return container[number];
}

template<typename Container>
class AtItemAccess
{
public:
  using iterator = std::size_t;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using value_type = typename Container::value_type;

  static iterator begin(const Container&);
  static iterator end(const Container& container);
  static reference access(Container& container, iterator number);
};

template<typename Container>
typename AtItemAccess<Container>::iterator AtItemAccess<Container>::begin(const Container&)
{
  return 0;
}

template<typename Container>
typename AtItemAccess<Container>::iterator AtItemAccess<Container>::end(const Container& container)
{
  return container.size();
}

template<typename Container>
typename AtItemAccess<Container>::reference
AtItemAccess<Container>::access(Container& container, AtItemAccess::iterator number)
{
  return container.at(number);
}

template<typename Container>
class IteratorItemAccess
{
public:
  using iterator = typename Container::iterator;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using value_type = typename Container::value_type;

  static iterator begin(Container& container);
  static iterator end(Container& container);
  static reference access(Container&, iterator number);
};

template<typename Container>
typename IteratorItemAccess<Container>::iterator IteratorItemAccess<Container>::begin(Container& container)
{
  return container.begin();
}

template<typename Container>
typename IteratorItemAccess<Container>::iterator IteratorItemAccess<Container>::end(Container& container)
{
  return container.end();
}

template<typename Container>
typename IteratorItemAccess<Container>::reference
IteratorItemAccess<Container>::access(Container&, IteratorItemAccess::iterator number)
{
  return *number;
}

template<template<typename Container> class Access, typename Container>
void sort(Container& container,
  const std::function<bool(const typename Container::reference, const typename Container::reference)>& comparator)
{
  for (typename Access<Container>::iterator i = Access<Container>::begin(container);
    i != Access<Container>::end(container); i++)
  {
    auto minOrMax = i;
    for (typename Access<Container>::iterator j = i;
      j != Access<Container>::end(container); j++)
    {
      if (comparator(Access<Container>::access(container, minOrMax),
        Access<Container>::access(container, j)))
      {
        minOrMax = j;
      }
    }
    std::swap(Access<Container>::access(container, i),
      Access<Container>::access(container, minOrMax));

  }
}

#endif
