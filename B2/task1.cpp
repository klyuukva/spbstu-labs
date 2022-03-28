#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>
#include <map>

#include "queue_with_priority.hpp"
#include "tasks.hpp"
#include "auxiliary-functions.hpp"

using priority = QueueWithPriority<std::string>::Priority;
using queueFunction = std::function<void(QueueWithPriority<std::string>& queue, std::ostream& out)>;

static std::istream& operator>>(std::istream& in, queueFunction& function);
static queueFunction parseAdd(std::istream& in);
static queueFunction parseGet(std::istream&);
static queueFunction parseAccelerate(std::istream&);

static void outputErrorMessage(QueueWithPriority<std::string>&, std::ostream& out);

void task1(std::istream& in, std::ostream& out)
{
  QueueWithPriority<std::string> queue;

  while (in >> std::ws && !in.eof())
  {
    queueFunction function;
    in >> function;

    if (in.fail())
    {
      throw std::ios_base::failure("Couldn't read file or wrong input.");
    }

    function(queue, out);
  }

  if (!in.eof())
  {
    throw std::ios_base::failure("Couldn't read file or wrong input.");
  }
}

std::istream& operator>>(std::istream& in, queueFunction& function)
{
  static const std::map<std::string, queueFunction (*)(std::istream&)> functions =
    {
      {"add", parseAdd},
      {"accelerate", parseAccelerate},
      {"get", parseGet}
    };

  std::string command;
  in >> std::ws >> command;

  if (in.fail())
  {
    return in;
  }

  auto iterator = functions.find(command);
  if (iterator != functions.end())
  {
    function = iterator->second(in);
  }
  else
  {
    function = outputErrorMessage;
  }
  return in;
}

queueFunction parseAdd(std::istream& in)
{

  std::string priorityString;
  in >> skipSpacesExcludingNewline >> priorityString;

  if (in.fail())
  {
    return outputErrorMessage;
  }

  std::string data;
  getline(in >> skipSpacesExcludingNewline, data);

  if (in.fail() || data.empty())
  {
    return outputErrorMessage;
  }

  static const std::map<std::string, priority> priorities =
    {
      {"low", priority::LOW},
      {"normal", priority::NORMAL},
      {"high", priority::HIGH}
    };

  priority tempPriority = priority::LOW;
  auto iterator = priorities.find(priorityString);
  if (iterator != priorities.end())
  {
    tempPriority = iterator->second;
  }
  else
  {
    return outputErrorMessage;
  }

  return [tempPriority, data](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    queue.add(tempPriority, data);
  };
}

queueFunction parseGet(std::istream&)
{
  return [](QueueWithPriority<std::string>& queue, std::ostream& out)
  {
    if (!queue.empty())
    {
      queue.handleAndPopFront([&out](const std::string& str)
      {
        out << str << "\n";
      });
    }
    else
    {
      out << "<EMPTY>\n";
    }
  };
}

queueFunction parseAccelerate(std::istream&)
{
  return [](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    queue.accelerate();
  };
}

void outputErrorMessage(QueueWithPriority<std::string>&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
