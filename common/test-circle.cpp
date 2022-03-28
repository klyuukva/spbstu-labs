#define _USE_MATH_DEFINES

#include <cmath>
#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(TestCircle, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestCorrectCircleWithAllPositiveValues)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Circle(9, {8, 7}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectCircleWithNegativeYCoordinate)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Circle(9, {8, -7}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectCircleWithNegativeXCoordinate)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Circle(9, {-8, 7}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectCircleWithAllZeroCoordinates)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Circle(9, {0, 0}));
  }

  BOOST_AUTO_TEST_CASE(TestNegativeRadiusValue)
  {
    BOOST_CHECK_THROW(pozdnova::Circle(-9, {8, 7}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestZeroRadiusValue)
  {
    BOOST_CHECK_THROW(pozdnova::Circle(0, {8, 7}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    pozdnova::Circle circle(9, {8, 7});
    double correctArea = 9 * 9 * M_PI;

    double area = circle.getArea();

    BOOST_TEST(correctArea == area);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveToPoint)
  {
    pozdnova::Circle circle(9, {8, 7});

    double area = circle.getArea();
    circle.move({5, 4});
    double movedArea = circle.getArea();

    BOOST_TEST(area == movedArea);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveOnAxis)
  {
    pozdnova::Circle circle(9, {8, 7});

    double area = circle.getArea();
    circle.move(5, 4);
    double movedArea = circle.getArea();

    BOOST_TEST(area == movedArea);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterScale)
  {
    pozdnova::Circle circle(9, {8, 7});
    double correctArea = 5 * 9 * 5 * 9 * M_PI;

    circle.scale(5);
    double area = circle.getArea();

    BOOST_TEST(area == correctArea);
  }

  BOOST_AUTO_TEST_CASE(TestMoveToPoint)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.move({5, 4});
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == 9 + 9);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestMoveOnAxis)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.move(5, 4);
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 8);
    BOOST_TEST(frame.pos.y == 4 + 7);
    BOOST_TEST(frame.width == 9 + 9);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRect)
  {
    pozdnova::Circle circle(9, {8, 7});

    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 8);
    BOOST_TEST(frame.pos.y == 7);
    BOOST_TEST(frame.width == 9 + 9);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredFrameRectAfterMoveToPoint)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.move({5, 4});
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == 9 + 9);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredFrameRectAfterMoveOnAxis)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.move(5, 4);
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 8);
    BOOST_TEST(frame.pos.y == 4 + 7);
    BOOST_TEST(frame.width == 9 + 9);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.scale(5);
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 8);
    BOOST_TEST(frame.pos.y == 7);
    BOOST_TEST(frame.width == (9 + 9) * 5);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestScaleAfterMoveToPoint)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.move({5, 4});
    circle.scale(3);
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == (9 + 9) * 3);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestScaleAfterMoveOnAxis)
  {
    pozdnova::Circle circle(9, {8, 7});

    circle.move(5, 4);
    circle.scale(3);
    pozdnova::rectangle_t frame = circle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 8);
    BOOST_TEST(frame.pos.y == 4 + 7);
    BOOST_TEST(frame.width == (9 + 9) * 3);
    BOOST_TEST(frame.width == frame.height);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeRatioValue)
  {
    pozdnova::Circle circle(9, {8, 7});

    BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroRatioValue)
  {
    pozdnova::Circle circle(9, {8, 7});

    BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRotate)
  {
    pozdnova::Circle circle(9, {8, 7});
    pozdnova::rectangle_t frameRectBeforeRotate = circle.getFrameRect();
    double areaBeforeRotate = circle.getArea();
    circle.rotate(45);

    pozdnova::rectangle_t frameRectAfterRotate = circle.getFrameRect();
    double areaAfterRotate = circle.getArea();

    BOOST_TEST(frameRectAfterRotate.pos.x == 8);
    BOOST_TEST(frameRectAfterRotate.pos.y == 7);
    BOOST_TEST(frameRectAfterRotate.width == frameRectBeforeRotate.width);
    BOOST_TEST(frameRectAfterRotate.height == frameRectBeforeRotate.height);
    BOOST_TEST(areaAfterRotate == areaBeforeRotate);
  }


BOOST_AUTO_TEST_SUITE_END()
