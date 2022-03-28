#include <iostream>
#include <stdexcept>

#include"../common/rectangle.hpp"
#include"../common/circle.hpp"

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
  Rectangle rectangle({4.5, 5.0, 0.0, 2.0});
  Circle circle(5.0, {3.0, 6.5});

  std::cout << "RECTANGLE ";
  testShape(rectangle);

  std::cout << "CIRCLE ";
  testShape(circle);

  return 0;

}
