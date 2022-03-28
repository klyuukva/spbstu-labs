#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(TestRectangle, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestCorrectRectangleWithAllPositiveValues)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Rectangle({9, 8, 7, 6}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectRectangleWithNegativeXCoordinate)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Rectangle({9, 8, -7, 6}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectRectangleWithNegativeYCoordinate)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Rectangle({9, 8, 7, -6}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectRectangleWithAllZeroCoordinates)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Rectangle({9, 8, 0, 0}));
  }

  BOOST_AUTO_TEST_CASE(TestNegativeWidthValue)
  {
    BOOST_CHECK_THROW(pozdnova::Rectangle({-9, 8, 7, 6}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestNegativeHeightValue)
  {
    BOOST_CHECK_THROW(pozdnova::Rectangle({9, -8, 7, 6}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestZeroWidthValue)
  {
    BOOST_CHECK_THROW(pozdnova::Rectangle({0, 8, 7, 6}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestZeroHeightValue)
  {
    BOOST_CHECK_THROW(pozdnova::Rectangle({9, 0, 7, 6}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});
    double correctArea = 9 * 8;

    double area = rectangle.getArea();

    BOOST_TEST(correctArea == area);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveToPoint)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    double area = rectangle.getArea();
    rectangle.move({5, 4});
    double movedArea = rectangle.getArea();

    BOOST_TEST(area == movedArea);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveOnAxis)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    double area = rectangle.getArea();
    rectangle.move(5, 4);
    double movedArea = rectangle.getArea();

    BOOST_TEST(area == movedArea);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterScale)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});
    double correctArea = 5 * 5 * 9 * 8;

    rectangle.scale(5);
    double area = rectangle.getArea();

    BOOST_TEST(area == correctArea);
  }

  BOOST_AUTO_TEST_CASE(TestMoveToPoint)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.move({5, 4});
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
  }

  BOOST_AUTO_TEST_CASE(TestMoveOnAxis)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.move(5, 4);
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 7);
    BOOST_TEST(frame.pos.y == 4 + 6);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRect)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 7);
    BOOST_TEST(frame.pos.y == 6);
    BOOST_TEST(frame.width == 9);
    BOOST_TEST(frame.height == 8);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredFrameRectAfterMoveToPoint)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.move({5, 4});
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == 9);
    BOOST_TEST(frame.height == 8);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredFrameRectAfterMoveOnAxis)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.move(5, 4);
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 7);
    BOOST_TEST(frame.pos.y == 4 + 6);
    BOOST_TEST(frame.width == 9);
    BOOST_TEST(frame.height == 8);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.scale(5);
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 7);
    BOOST_TEST(frame.pos.y == 6);
    BOOST_TEST(frame.width == 9 * 5);
    BOOST_TEST(frame.height == 8 * 5);
  }

  BOOST_AUTO_TEST_CASE(TestScaleAfterMoveToPoint)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.move({5, 4});
    rectangle.scale(3);
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == 9 * 3);
    BOOST_TEST(frame.height == 8 * 3);
  }

  BOOST_AUTO_TEST_CASE(TestScaleAfterMoveOnAxis)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    rectangle.move(5, 4);
    rectangle.scale(3);
    pozdnova::rectangle_t frame = rectangle.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 7);
    BOOST_TEST(frame.pos.y == 4 + 6);
    BOOST_TEST(frame.width == 9 * 3);
    BOOST_TEST(frame.height == 8 * 3);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeRatioValue)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    BOOST_CHECK_THROW(rectangle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroRatioValue)
  {
    pozdnova::Rectangle rectangle({9, 8, 7, 6});

    BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRotate)
  {
    pozdnova::Rectangle rectangle({9, 8, {7, 6}});
    double areaBeforeRotate = rectangle.getArea();
    double expectedFrameWidth = 12.0208;
    double expectedFrameHeight = 12.0208;

    rectangle.rotate(45);

    pozdnova::rectangle_t frameAfterRotate = rectangle.getFrameRect();
    double areaAfterRotate = rectangle.getArea();

    BOOST_TEST(frameAfterRotate.pos.x == 7);
    BOOST_TEST(frameAfterRotate.pos.y == 6);
    BOOST_TEST(expectedFrameWidth == frameAfterRotate.width);
    BOOST_TEST(expectedFrameHeight == frameAfterRotate.height);
    BOOST_TEST(areaBeforeRotate == areaAfterRotate);

  }

BOOST_AUTO_TEST_SUITE_END()
