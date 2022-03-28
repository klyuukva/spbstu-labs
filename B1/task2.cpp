#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

void copyFile(const char* name, std::ostream& out)
{
  if (name == nullptr)
  {
    throw std::invalid_argument("File don't exist.");
  }

  size_t BUFFERSIZE = 1024;
  std::ifstream file(name);

  if (!file.is_open())
  {
    throw std::logic_error("Can't open file.");
  }

  char* arr = static_cast<char*>(calloc(BUFFERSIZE, sizeof(char)));
  size_t countElements = 0;

  while (file)
  {
    file.read(&arr[countElements], BUFFERSIZE - countElements);

    countElements += file.gcount();

    if (countElements == BUFFERSIZE)
    {
      char* massive = static_cast<char*>(realloc(arr, BUFFERSIZE * 1.5 * sizeof(char)));
      if (massive == nullptr)
      {
        free(arr);
        throw std::bad_alloc();
      }
      arr = massive;
      BUFFERSIZE *= 1.5;
    }

  }

  std::vector<char> outputVector(&arr[0], &arr[countElements]);
  out.write(&outputVector[0], outputVector.size());
  free(arr);
}
