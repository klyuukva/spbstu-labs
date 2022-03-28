#include <iostream>
#include <random>
#include <functional>
#include "implementation.hpp"

void fillRandom(double* array, int size)
{
  if (size < 0)
  {
    throw std::invalid_argument("Size can't be negative or zero.");
  }

  if (array == nullptr)
  {
    throw std::invalid_argument("Array is empty.");
  }

  static std::random_device rd;
  std::uniform_real_distribution<double> dis(-1.0, 1.0);

  for (int i = 0; i < size; i++)
  {
    array[i] = dis(rd);
  }
}

void sortForRandomArray(std::vector<double>& vector, const char* sortMethod)
{
  std::function<bool(double, double)> method = getSortMethod<double>(sortMethod);
  sort<IndexItemAccess>(vector, method);
}
