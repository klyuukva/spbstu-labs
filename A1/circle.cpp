#include "circle.hpp"

#include <stdexcept>
#include <cmath>

Circle::Circle(double radius, const point_t& point) :
  radius_(radius),
  point_(point)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Wrong value of radius: value cannot be negative or equals zero");
  }
}

double Circle::getArea() const noexcept
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {radius_ * 2, radius_ * 2, point_};
}

void Circle::move(const point_t& point) noexcept
{
  point_ = point;
}

void Circle::move(double dx, double dy) noexcept
{
  point_.x += dx;
  point_.y += dy;
}
