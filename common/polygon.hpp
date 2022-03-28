#ifndef POZDNOVA_MARIA_A3_TEST_POLYGON_HPP
#define POZDNOVA_MARIA_A3_TEST_POLYGON_HPP

#include "base-types.hpp"
#include "shape.hpp"
#include <memory>

namespace pozdnova
{
  using array = std::unique_ptr<point_t[]>;

  class Polygon : public Shape
  {
  public:
    Polygon(const point_t* points, std::size_t quantity);

    double getArea() const noexcept override;
    point_t getBarycenter() const noexcept;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double ratio) override;
    void rotate(double degrees) noexcept override;
    bool isConvex();
  private:
    array points_;
    std::size_t quantity_;
  };
}
#endif //POZDNOVA_MARIA_A3_TEST_POLYGON_HPP
