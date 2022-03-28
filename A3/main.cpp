#include <iostream>
#include <stdexcept>
#include <memory>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace pozdnova;

void testShape(Shape& form)
{
  std::cout << "Area: " << form.getArea() << " ";
  rectangle_t figure = form.getFrameRect();
  std::cout << "Frame sides: " << figure.width << " " << figure.height << "  Coordinates: " << figure.pos.x << " "
    << figure.pos.y << ' ';
  form.move(4.0, 4.0);
  figure = form.getFrameRect();
  std::cout << "Displacement to a specific point. Coordinates:  " << figure.pos.x << " " << figure.pos.y << ' ';
  form.move({1.0, 2.0});
  std::cout << "Displacement of a point folding its coordinates with a given. Coordinates:  " << figure.pos.x << " "
    << figure.pos.y << ' ';
  try
  {
    form.scale(2);
    std::cout << "Scale figure with ratio. Sides  " << figure.width << " " << figure.height << "  Coordinates: "
      << figure.pos.x << " " << figure.pos.y << ' ';
  }
  catch (const std::exception& error)
  {
    std::cerr << " Error found in scale " << error.what();
  }
}

int main()
{
  shape rectangle = nullptr;
  std::shared_ptr<Circle> circle = nullptr;
  try
  {
    rectangle = std::make_shared<Rectangle>(rectangle_t{9, 8, 7, 6});
    circle = std::make_shared<Circle>(9, point_t{8, 7});
  }

  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 2;
  }

  std::cout << "RECTANGLE ";
  testShape(*rectangle);

  std::cout << "CIRCLE ";
  testShape(*circle);

  std::cout << "COMPOSITE SHAPE";
  CompositeShape compositeShape{};

  try
  {
    compositeShape.add(rectangle);
    compositeShape.add(circle);
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 2;
  }

  std::cout << " Area: " << compositeShape.getArea();

  try
  {
    Rectangle frame(compositeShape.getFrameRect());
    std::cout << "Frame sides: " << frame.getFrameRect().width << " " << frame.getFrameRect().height
      << "  Coordinates: " << frame.getFrameRect().pos.x << " "
      << frame.getFrameRect().pos.y << ' ';
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 2;
  }

  compositeShape.move(4.0, 4.0);
  Rectangle figure = compositeShape.getFrameRect();
  std::cout << "Displacement to a specific point. Coordinates:  " << compositeShape.getFrameRect().pos.x << " "
    << compositeShape.getFrameRect().pos.y
    << ' ';
  compositeShape.move({1.0, 2.0});
  std::cout << "Displacement of a point folding its coordinates with a given. Coordinates:  "
    << compositeShape.getFrameRect().pos.x
    << " "
    << compositeShape.getFrameRect().pos.y << ' ';

  try
  {
    compositeShape.scale(2);
    Rectangle frameAfterRemove = compositeShape.getFrameRect();
    std::cout << "Scale figure with ratio. Sides  " << frameAfterRemove.getFrameRect().width << " "
      << frameAfterRemove.getFrameRect().height
      << "  Coordinates: "
      << frameAfterRemove.getFrameRect().pos.x << " " << frameAfterRemove.getFrameRect().pos.y << ' '
      << " Area after scale: "
      << frameAfterRemove.getArea();
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
  }

  std::cout << " Size: " << compositeShape.size();

  return 0;

}
