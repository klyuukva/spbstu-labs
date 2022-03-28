#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle)
{
  if ((rectangle_.width <= 0) || (rectangle_.height <= 0))
  {
    throw std::invalid_argument("Wrong value of height or width: values cannot be negetive or equals zero");
  }
}

double Rectangle::getArea() const noexcept
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return rectangle_;
}

void Rectangle::move(const point_t& point) noexcept
{
  rectangle_.pos = point;
}

void Rectangle::move(double dx, double dy) noexcept
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}
