#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace pozdnova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t& rectangle);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double ratio) override;
    void rotate(double degrees) noexcept override;
  private:
    rectangle_t rectangle_;
    double angle_;
  };
}
#endif // RECTANGLE_HPP
