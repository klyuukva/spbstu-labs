#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace pozdnova
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t& point) noexcept = 0;
    virtual void move(double dx, double dy) noexcept = 0;
    virtual void scale(double ratio) = 0;
    virtual void rotate(double degrees) noexcept = 0;
  };
}
#endif // !SHAPE_HPP
