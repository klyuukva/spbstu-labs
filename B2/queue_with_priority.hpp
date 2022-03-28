#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <stdexcept>
#include <list>
#include <iostream>

template<typename T>
class QueueWithPriority
{
public:
  using reference = typename std::list<T>::reference;
  using value_type = typename std::list<T>::value_type;

  enum Priority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void add(const Priority& priority, const T& data);
  void accelerate();
  bool empty() const noexcept;

  template<typename Handler>
  void handleAndPopFront(const Handler& handler);

private:
  std::list<T> priorityQueue_[3];
};

template<typename T>
void QueueWithPriority<T>::add(const Priority& priority, const T& data)
{
  priorityQueue_[priority].push_back(data);
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  priorityQueue_[HIGH].splice(priorityQueue_[HIGH].end(), priorityQueue_[LOW]);
}

template<typename T>
bool QueueWithPriority<T>::empty() const noexcept
{
  return priorityQueue_[LOW].empty() && priorityQueue_[NORMAL].empty() && priorityQueue_[HIGH].empty();
}

template<typename T>
template<typename Handler>
void QueueWithPriority<T>::handleAndPopFront(const Handler& handler)
{
  if (empty())
  {
    return;
  }

  int queueIndex = 0;
  for (int i = 2; i >= 0; --i)
  {
    if (!priorityQueue_[i].empty())
    {
      queueIndex = i;
      break;
    }
  }

  try
  {
    handler(priorityQueue_[queueIndex].front());
  }
  catch (const std::exception& error)
  {
    priorityQueue_[queueIndex].pop_front();
    throw error;
  }
  priorityQueue_[queueIndex].pop_front();
}

#endif
