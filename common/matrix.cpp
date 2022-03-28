#include "matrix.hpp"
#include <stdexcept>

pozdnova::Matrix::Matrix(const pozdnova::Matrix& matrix) :
  layer_(matrix.layer_),
  shapeQuantity_(matrix.shapeQuantity_),
  matrix_(std::make_unique<shape[]>(layer_ * shapeQuantity_))
{
  for (size_t i = 0; i < layer_ * shapeQuantity_; ++i)
  {
    matrix_[i] = matrix.matrix_[i];
  }
}

pozdnova::Matrix& pozdnova::Matrix::operator=(const pozdnova::Matrix& matrix)
{
  if (&matrix == this)
  {
    return *this;
  }
  else
  {
    array tempMatrix = std::make_unique<shape[]>(layer_ * shapeQuantity_);
    layer_ = matrix.layer_;
    shapeQuantity_ = matrix.shapeQuantity_;
    for (size_t i = 0; i < (matrix.shapeQuantity_ * matrix.layer_); ++i)
    {
      matrix_[i] = matrix.matrix_[i];
    }
    return *this;
  }
}

pozdnova::Matrix pozdnova::Matrix::layerFilling(const CompositeShape& tempShape)
{
  if (tempShape.size() == 0)
  {
    throw std::invalid_argument("Composite shape is empty.");
  }
  Matrix matrix;
  for (size_t i = 0; i < tempShape.size(); ++i)
  {
    size_t countLayer = 0;
    size_t countShapeQuantity = 0;
    if (i == 0)
    {
      matrix.add(countLayer, countShapeQuantity, tempShape[i]);
      countLayer++;
      countShapeQuantity++;
      continue;
    }

    for (size_t j = 0; j < matrix.getLayers(); ++j)
    {
      for (size_t k = 0; k < matrix.getQuantity(); ++k)
      {
        if (isOverlap(tempShape[i]->getFrameRect(), matrix[j][k]->getFrameRect()))
        {
          countLayer = j + 1;
          countShapeQuantity = 0;
          break;
        }
        else
        {
          countShapeQuantity = k + 1;
          countLayer = j;
        }
      }
      if (countLayer == 0)
      {
        break;
      }
    }
    matrix.add(countLayer, countShapeQuantity, tempShape[i]);
  }
  return matrix;
}

pozdnova::array pozdnova::Matrix::operator[](size_t ind) const
{
  if (ind >= layer_)
  {
    throw std::out_of_range("Index out of range");
  }
  array tempMatrix = std::make_unique<shape[]>(shapeQuantity_);
  for (size_t i = 0; i < getQuantityOfLayer(ind); ++i)
  {
    tempMatrix[i] = matrix_[ind * shapeQuantity_ + i];
  }
  return tempMatrix;
}

size_t pozdnova::Matrix::getLayers() const noexcept
{
  return layer_;
}

size_t pozdnova::Matrix::getQuantity() const noexcept
{
  return shapeQuantity_;
}

size_t pozdnova::Matrix::getQuantityOfLayer(const size_t layer) const
{
  for (size_t i = 0; i < shapeQuantity_; ++i)
  {
    if (matrix_[layer * shapeQuantity_ + i] == nullptr)
    {
      return i;
    }
  }
  return shapeQuantity_;
}

void pozdnova::Matrix::add(size_t layers, size_t shapeQuantity, const pozdnova::shape& tempShape)
{
  size_t tempLayers;
  size_t tempShapeQuantity;
  if (layer_ == layers)
  {
    tempLayers = layers + 1;
  }
  else
  {
    tempLayers = layer_;
  }

  if (shapeQuantity_ == shapeQuantity)
  {
    tempShapeQuantity = shapeQuantity + 1;
  }
  else
  {
    tempShapeQuantity = shapeQuantity_;
  }

  array tempMatrix = std::make_unique<shape[]>(tempLayers * tempShapeQuantity);
  for (size_t i = 0; i < tempLayers; ++i)
  {
    for (size_t j = 0; j < tempShapeQuantity; ++j)
    {
      if ((i == layer_) || (j == shapeQuantity_))
      {
        tempMatrix[i * tempShapeQuantity + j] = nullptr;
      }
      else
      {
        tempMatrix[i * tempShapeQuantity + j] = matrix_[i * shapeQuantity_ + j];
      }
    }
  }
  tempMatrix[layers * tempShapeQuantity + shapeQuantity] = tempShape;
  matrix_ = std::move(tempMatrix);
  layer_ = tempLayers;
  shapeQuantity_ = tempShapeQuantity;
}

bool pozdnova::Matrix::isOverlap(pozdnova::rectangle_t rectangle1, pozdnova::rectangle_t rectangle2) noexcept
{
  double dy = std::abs(std::abs(rectangle1.pos.y) - std::abs(rectangle2.pos.y));
  double dx = std::abs(std::abs(rectangle1.pos.x) - std::abs(rectangle2.pos.x));
  double heightSum = rectangle1.height + rectangle2.height;
  double widthSum = rectangle1.width + rectangle2.width;
  return (dy < (heightSum / 2)) && (dx < (widthSum / 2));
}
