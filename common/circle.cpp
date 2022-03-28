#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>

pozdnova::Circle::Circle(double radius, const point_t& point) :
  radius_(radius),
  point_(point)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Wrong value of radius: value cannot be negative or equals zero");
  }
}

double pozdnova::Circle::getArea() const noexcept
{
  return radius_ * radius_ * M_PI;
}

pozdnova::rectangle_t pozdnova::Circle::getFrameRect() const noexcept
{
  return {radius_ * 2, radius_ * 2, point_};
}

void pozdnova::Circle::move(const point_t& point) noexcept
{
  point_ = point;
}

void pozdnova::Circle::move(double dx, double dy) noexcept
{
  point_.x += dx;
  point_.y += dy;
}

void pozdnova::Circle::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("Wrong value of ratio: value must be positive and greater then zero");
  }
  radius_ *= ratio;
}

void pozdnova::Circle::rotate(double) noexcept
{ }
