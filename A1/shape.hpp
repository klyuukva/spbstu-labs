#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const noexcept = 0;
  virtual rectangle_t getFrameRect() const noexcept = 0;
  virtual void move(const point_t& point) noexcept = 0;
  virtual void move(double dx, double dy) noexcept = 0;
};

#endif // !SHAPE_HPP
