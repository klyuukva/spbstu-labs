#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

pozdnova::Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle),
  angle_(0)
{
  if ((rectangle_.width <= 0) || (rectangle_.height <= 0))
  {
    throw std::invalid_argument("Wrong value of height or width: values cannot be negetive or equals zero");
  }
}

double pozdnova::Rectangle::getArea() const noexcept
{
  return rectangle_.width * rectangle_.height;
}

pozdnova::rectangle_t pozdnova::Rectangle::getFrameRect() const noexcept
{
  return {rectangle_.width * std::abs(std::cos(angle_ * M_PI / 180)) + rectangle_.height *
    std::abs(std::sin(angle_ * M_PI / 180)), rectangle_.width *
    std::abs(std::sin(angle_ * M_PI / 180)) + rectangle_.height * std::abs(std::cos(angle_ * M_PI / 180)),
    {rectangle_.pos}};
}

void pozdnova::Rectangle::move(const point_t& point) noexcept
{
  rectangle_.pos = point;
}

void pozdnova::Rectangle::move(double dx, double dy) noexcept
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void pozdnova::Rectangle::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("Wrong value of ratio: value must be positive and greater then zero");
  }
  rectangle_.height *= ratio;
  rectangle_.width *= ratio;
}

void pozdnova::Rectangle::rotate(double degrees) noexcept
{
  angle_ += degrees;
}
