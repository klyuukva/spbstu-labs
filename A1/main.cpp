#include <iostream>
#include <stdexcept>

#include"rectangle.hpp"
#include"circle.hpp"

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
}

int main()
{
  Rectangle rectangle({4.5, 5.0, 0.0, 2.0});
  Circle circle(5.0, {3.0, 6.5});

  std::cout << "RECTANGLE ";
  testShape(rectangle);

  std::cout << "CIRCLE ";
  testShape(circle);

  std::cout << "WRONG VALUES ";
  try
  {
    std::cout << "Negative value in rectangle. ";
    Rectangle wrong_rectangle({-2.0, 8.0, 0.5, 3.6});
    std::cout << "Rectangle({ -2.0, 8.0, 0.5, 3.6 }) ";
  }
  catch (const std::invalid_argument& error)
  {
    std::cout << "Error expected: " << error.what() << " ";
  }

  try
  {
    std::cout << "Zero value in circle ";
    Circle wrong_circle(0.0, {3.0, 6.5});
    std::cout << "Circle(0.0, { 3.0, 6.5 }) ";
  }
  catch (const std::invalid_argument& error)
  {
    std::cout << "Error expected: " << error.what() << " ";
  }

  return 0;

}
