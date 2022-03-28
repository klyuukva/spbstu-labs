#ifndef POZDNOVA_MARIA_A3_TEST_MATRIX_HPP
#define POZDNOVA_MARIA_A3_TEST_MATRIX_HPP

#include <memory>
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "shape.hpp"

namespace pozdnova
{
  using array = std::unique_ptr<std::shared_ptr<Shape>[]>;

  class Matrix
  {
  public:
    static Matrix layerFilling(const CompositeShape& tempShape);
    Matrix() noexcept = default;
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept = default;
    ~Matrix() = default;

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) noexcept = default;

    array operator[](size_t ind) const;

    size_t getLayers() const noexcept;
    size_t getQuantity() const noexcept;
    size_t getQuantityOfLayer(const size_t layer) const;

  private:
    size_t layer_ = 0;
    size_t shapeQuantity_ = 0;
    array matrix_;
    static bool isOverlap(const pozdnova::rectangle_t rectangle1, const pozdnova::rectangle_t rectangle2) noexcept;
    void add(size_t layers, size_t shapeQuantity, const shape& tempShape);

  };
}
#endif //POZDNOVA_MARIA_A3_TEST_MATRIX_HPP
