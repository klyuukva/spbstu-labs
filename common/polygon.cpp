#include "polygon.hpp"
#include <limits>
#include <cmath>

pozdnova::Polygon::Polygon(const pozdnova::point_t* points, std::size_t quantity) :
  points_(std::make_unique<point_t[]>(quantity)),
  quantity_(quantity)
{
  if (quantity_ < 3)
  {
    throw std::out_of_range("Quantity of points out of range.");
  }
  for (size_t i = 0; i < quantity_; ++i)
  {
    points_[i] = points[i];
  }
  if (!isConvex())
  {
    throw std::invalid_argument("Polygon must be convex");
  }
}

double pozdnova::Polygon::getArea() const noexcept
{
  double area = points_[quantity_ - 1].x * points_[0].y - points_[quantity_ - 1].y * points_[0].x;
  for (size_t i = 0; i < quantity_ - 1; ++i)
  {
    area += (points_[i].x * points_[i + 1].y) - (points_[i + 1].x * points_[i].y);
  }
  return std::abs(area * 0.5);
}

pozdnova::point_t pozdnova::Polygon::getBarycenter() const noexcept
{
  point_t barycenter{};
  double sumX = 0;
  double sumY = 0;
  for (size_t i = 0; i < quantity_; ++i)
  {
    sumX += points_[i].x;
    sumY += points_[i].y;
  }
  return {barycenter.x = sumX / quantity_, barycenter.y = sumY / quantity_};
}

pozdnova::rectangle_t pozdnova::Polygon::getFrameRect() const noexcept
{
  rectangle_t frame{0, 0, {}};
  double minY = +std::numeric_limits<double>::infinity();
  double minX = +std::numeric_limits<double>::infinity();
  double maxY = -std::numeric_limits<double>::infinity();
  double maxX = -std::numeric_limits<double>::infinity();

  for (size_t i = 0; i < quantity_; ++i)
  {
    if (points_[i].x < minX)
    {
      minX = points_[i].x;
    }
    if (points_[i].y < minY)
    {
      minY = points_[i].y;
    }
    if (points_[i].x > maxX)
    {
      maxX = points_[i].x;
    }
    if (points_[i].y > maxY)
    {
      maxY = points_[i].y;
    }
  }
  frame = {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
  return frame;
}

void pozdnova::Polygon::move(const pozdnova::point_t& point) noexcept
{
  const point_t barycenter = getBarycenter();
  move(point.x - barycenter.x, point.y - barycenter.y);
}

void pozdnova::Polygon::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < quantity_; ++i)
  {
    points_[i].x += dx;
    points_[i].y += dy;
  }
}

void pozdnova::Polygon::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("Wrong value of ratio: value must be positive and greater then zero");
  }

  const point_t barycenter = getBarycenter();
  for (size_t i = 0; i < quantity_; ++i)
  {
    points_[i].y += (points_[i].y - barycenter.y) * (ratio - 1);
    points_[i].x += (points_[i].x - barycenter.x) * (ratio - 1);
  }
}

void pozdnova::Polygon::rotate(double degrees) noexcept
{

  double cos = (std::cos(degrees * M_PI / 180));
  double sin = (std::sin(degrees * M_PI / 180));
  point_t barycenter = getFrameRect().pos;
  for (size_t i = 0; i < quantity_; ++i)
  {
    double dx = points_[i].x - barycenter.x;
    double dy = points_[i].y - barycenter.y;
    points_[i].x = barycenter.x + dx * cos - dy * sin;
    points_[i].y = barycenter.y + dx * sin + dy * cos;
  }
}

static double cross(const pozdnova::point_t& point1, const pozdnova::point_t& point2)
{
  return point1.x * point2.y - point1.y * point2.x;
}

static bool isNegative(const pozdnova::point_t& point1, const pozdnova::point_t& point2)
{
  return cross(point1, point2) < 0;
}

bool pozdnova::Polygon::isConvex()
{
  bool convex = true;
  bool flag = false;
  for (size_t i = 0; i < quantity_; ++i)
  {
    point_t& a = points_[i];
    point_t& b = points_[(i + 1) % quantity_];
    point_t& c = points_[(i + 2) % quantity_];
    const point_t& ab{b.x - a.x, b.y - a.y};
    const point_t& bc{c.x - b.x, c.y - b.y};

    if (i == 0)
    {
      flag = isNegative(ab, bc);
    }
    else if (isNegative(ab, bc) != flag)
    {
      convex = false;
      break;
    }
  }
  return convex;
}
