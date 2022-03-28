#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace pozdnova
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t& point);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double ratio) override;
    void rotate(double degrees) noexcept override;
  private:
    double radius_;
    point_t point_;
  };
}
#endif // !CIRCLE_HPP
