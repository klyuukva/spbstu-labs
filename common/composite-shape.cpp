#include <stdexcept>
#include <limits>
#include <cmath>
#include "composite-shape.hpp"
#include "base-types.hpp"

pozdnova::CompositeShape::CompositeShape(const CompositeShape& compositeShape) :
  shapeArray_(std::make_unique<shape[]>(compositeShape.capacity_)),
  size_(compositeShape.size_),
  capacity_(compositeShape.capacity_)
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapeArray_[i] = compositeShape[i];
  }
}

pozdnova::CompositeShape& pozdnova::CompositeShape::operator=(const pozdnova::CompositeShape& compositeShape)
{
  if (&compositeShape == this)
  {
    return *this;
  }
  else
  {
    capacity_ = compositeShape.capacity_;
    size_ = compositeShape.size_;
    array shapeArray(std::make_unique<shape[]>(compositeShape.capacity_));
    for (size_t i = 0; i < size_; ++i)
    {
      shapeArray[i] = compositeShape.shapeArray_[i];
    }
    shapeArray_.swap(shapeArray);
  }
  return *this;
}

double pozdnova::CompositeShape::getArea() const noexcept
{
  double figureArea = 0;
  for (size_t i = 0; i < size_; i++)
  {
    figureArea += shapeArray_[i]->getArea();
  }
  return figureArea;
}

pozdnova::rectangle_t pozdnova::CompositeShape::getFrameRect() const noexcept
{
  rectangle_t frame{};
  if (empty())
  {
    frame = {0, 0, {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()}};
  }
  else
  {
    pozdnova::rectangle_t testFrame = shapeArray_[0]->getFrameRect();
    point_t upperRightPoint = {testFrame.pos.x + testFrame.width / 2, testFrame.pos.y + testFrame.width / 2};
    point_t bottomLeftPoint = {testFrame.pos.x - testFrame.width / 2, testFrame.pos.y - testFrame.width / 2};
    for (size_t i = 0; i < size_; i++)
    {
      rectangle_t shapeFrame = shapeArray_[i]->getFrameRect();
      double x = shapeFrame.width / 2;
      double y = shapeFrame.height / 2;
      point_t shapeUpperRightPoint = {shapeFrame.pos.x + x, shapeFrame.pos.y + y};
      point_t shapeBottomLeftPoint = {shapeFrame.pos.x - x, shapeFrame.pos.y - y};

      if (upperRightPoint.x < shapeUpperRightPoint.x)
      {
        upperRightPoint.x = shapeUpperRightPoint.x;
      }
      if (upperRightPoint.y < shapeUpperRightPoint.y)
      {
        upperRightPoint.y = shapeUpperRightPoint.y;
      }
      if (bottomLeftPoint.x > shapeBottomLeftPoint.x)
      {
        bottomLeftPoint.x = shapeBottomLeftPoint.x;
      }
      if (bottomLeftPoint.y > shapeBottomLeftPoint.y)
      {
        bottomLeftPoint.y = shapeBottomLeftPoint.y;
      }
    }
    double frameWidth = upperRightPoint.x - bottomLeftPoint.x;
    double frameHeight = upperRightPoint.y - bottomLeftPoint.y;
    point_t framePoint = {(bottomLeftPoint.x + upperRightPoint.x) / 2, (bottomLeftPoint.y + upperRightPoint.y) / 2};

    frame = {frameWidth, frameHeight, {framePoint.x, framePoint.y}};
  }
  return frame;
}

void pozdnova::CompositeShape::move(const point_t& point) noexcept
{
  point_t position = getPoint();
  move(point.x - position.x, point.y - position.y);
}

void pozdnova::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapeArray_[i]->move(dx, dy);
  }
}

void pozdnova::CompositeShape::scale(double ratio)
{
  point_t position = getFrameRect().pos;
  if (ratio <= 0)
  {
    throw std::invalid_argument("Wrong value of ratio: value must be positive and greater then zero");
  }

  for (size_t i = 0; i < size_; ++i)
  {
    point_t positionOfShape = shapeArray_[i]->getFrameRect().pos;
    double dx = (positionOfShape.x - position.x) * ratio;
    double dy = (positionOfShape.y - position.y) * ratio;
    shapeArray_[i]->move(dx, dy);
    shapeArray_[i]->scale(ratio);
  }
}

void pozdnova::CompositeShape::rotate(double degrees) noexcept
{
  point_t point = getFrameRect().pos;
  double cos = std::cos(degrees * M_PI / 180);
  double sin = std::sin(degrees * M_PI / 180);
  for (size_t i = 0; i < size_; ++i)
  {
    point_t shapePoint = shapeArray_[i]->getFrameRect().pos;
    shapeArray_[i]->move({point.x + cos * (shapePoint.x - point.x) - sin * (shapePoint.y - point.y),
      point.y + cos * (shapePoint.y - point.y) - sin * (shapePoint.x - point.x)});
    shapeArray_[i]->rotate(degrees);
  }
}

pozdnova::shape pozdnova::CompositeShape::operator[](const size_t ind) const
{
  if (ind >= size_)
  {
    throw std::out_of_range("Array out of range.");
  }
  return shapeArray_[ind];
}

void pozdnova::CompositeShape::add(const shape& figure)
{
  if (figure.get() == this)
  {
    throw std::invalid_argument("Сan't add the same figure.");
  }
  if (figure == nullptr)
  {
    throw std::invalid_argument("No figure to add.");
  }
  if (empty())
  {
    capacity_ = 1;
    array addedFigure = std::make_unique<shape[]>(capacity_);
    shapeArray_ = std::move(addedFigure);
    shapeArray_[size_++] = figure;
  }
  else
  {
    array addedFigure = std::make_unique<shape[]>(capacity_ * 2);
    capacity_ *= 2;
    for (size_t i = 0; i < size_; ++i)
    {
      addedFigure[i] = shapeArray_[i];
    }
    shapeArray_ = std::move(addedFigure);
    shapeArray_[size_++] = figure;
  }
}

void pozdnova::CompositeShape::remove()
{
  if (empty())
  {
    throw std::invalid_argument("Сan't delete a figure. The array is empty");
  }
  size_--;
  shapeArray_[size_].reset();
}

bool pozdnova::CompositeShape::empty() const noexcept
{
  return size_ == 0;
}

size_t pozdnova::CompositeShape::size() const noexcept
{
  return size_;
}

pozdnova::point_t pozdnova::CompositeShape::getPoint() const noexcept
{
  return getFrameRect().pos;
}
