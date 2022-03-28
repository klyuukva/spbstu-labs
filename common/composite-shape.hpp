#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <cstddef>
#include <memory>

#include "shape.hpp"

namespace pozdnova
{
  using shape = std::shared_ptr<Shape>;
  using array = std::unique_ptr<shape[]>;

  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept = default;
    CompositeShape(const CompositeShape& compositeShape);
    CompositeShape(CompositeShape&& compositeShape) noexcept = default;
    CompositeShape& operator=(const CompositeShape& compositeShape);
    CompositeShape& operator=(CompositeShape&& compositeShape) noexcept = default;
    ~CompositeShape() override = default;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double ratio) override;
    void rotate(double degrees) noexcept override;

    shape operator[](const size_t ind) const;
    void add(const shape& figure);
    void remove();
    bool empty() const noexcept;
    size_t size() const noexcept;
    point_t getPoint() const noexcept;

  private:
    array shapeArray_;
    size_t size_ = 0;
    size_t capacity_ = 0;
  };
}

#endif //POZDNOVA_MARIA_A2_TEST_COMPOSITE_SHAPE_HPP
