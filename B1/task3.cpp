#include <vector>

void modifyVector(std::vector<int>& arr)
{
  if (arr.empty())
  {
    return;
  }

  if (arr.back() == 1)
  {
    for (auto i = arr.begin(); i != arr.end(); i++)
    {
      if (*i % 2 == 0)
      {
        i = arr.erase(i) - 1;
      }
    }
  }
  else if (arr.back() == 2)
  {
    for (auto i = arr.begin(); i != arr.end(); i++)
    {
      if (*i % 3 == 0)
      {
        i = arr.insert(i + 1, 3, 1) + 2;
      }
    }
  }
}
