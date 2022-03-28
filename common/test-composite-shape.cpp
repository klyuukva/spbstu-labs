#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

inline void initializationOfCompositeShape(pozdnova::CompositeShape& testCompositeShape)
{
  std::shared_ptr<pozdnova::Rectangle> rectangle = std::make_shared<pozdnova::Rectangle>(
    pozdnova::rectangle_t{9, 8, 7, 6});
  std::shared_ptr<pozdnova::Circle> circle = std::make_shared<pozdnova::Circle>(9, pozdnova::point_t{8, 7});
  testCompositeShape.add(rectangle);
  testCompositeShape.add(circle);
}

BOOST_AUTO_TEST_SUITE(TestCompositeShape, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    pozdnova::CompositeShape testCompositeShape{};
    initializationOfCompositeShape(testCompositeShape);
    double area = 0;

    for (size_t i = 0; i < testCompositeShape.size(); ++i)
    {
      area += testCompositeShape[i]->getArea();
    }

    BOOST_TEST(area == testCompositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveToPoint)
  {
    pozdnova::CompositeShape testCompositeShape{};
    initializationOfCompositeShape(testCompositeShape);

    double area = testCompositeShape.getArea();
    testCompositeShape.move({6, 5});
    double movedArea = testCompositeShape.getArea();

    BOOST_TEST(area == movedArea);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveOnAxis)
  {
    pozdnova::CompositeShape testCompositeShape{};
    initializationOfCompositeShape(testCompositeShape);

    double area = testCompositeShape.getArea();
    testCompositeShape.move(6, 5);
    double movedArea = testCompositeShape.getArea();

    BOOST_TEST(area == movedArea);
  }

  BOOST_AUTO_TEST_CASE(TestGetAreaInEmptyCompositeShape)
  {
    pozdnova::CompositeShape compositeShape{};

    BOOST_TEST(compositeShape.getArea() == 0);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrame)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_TEST(frame.pos.x == 8);
    BOOST_TEST(frame.pos.y == 7);
    BOOST_TEST(frame.width == 18);
    BOOST_TEST(frame.height == 18);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredFrameRectAfterMoveToPoint)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.move({5, 4});
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == 18);
    BOOST_TEST(frame.height == 18);
  }

  BOOST_AUTO_TEST_CASE(TestUnalteredFrameRectAfterMoveOnAxis)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.move(5, 4);
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 8);
    BOOST_TEST(frame.pos.y == 4 + 7);
    BOOST_TEST(frame.width == 18);
    BOOST_TEST(frame.height == 18);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameInEmptyCompasiteShape)
  {
    pozdnova::CompositeShape compositeShape{};
    pozdnova::rectangle_t emptyFrame = compositeShape.getFrameRect();

    BOOST_CHECK(std::isnan(compositeShape.getFrameRect().pos.x));
    BOOST_CHECK(std::isnan(compositeShape.getFrameRect().pos.y));
    BOOST_TEST(emptyFrame.width == 0);
    BOOST_TEST(emptyFrame.height == 0);
  }

  BOOST_AUTO_TEST_CASE(TestMoveToPoint)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.move({5, 4});
    pozdnova::point_t point = compositeShape.getPoint();

    BOOST_TEST(point.x == 5);
    BOOST_TEST(point.y == 4);
  }

  BOOST_AUTO_TEST_CASE(TestMoveToPointInEmptyCompositeShape)
  {
    pozdnova::CompositeShape compositeShape{};
    compositeShape.move({5, 4});

    BOOST_CHECK(std::isnan(compositeShape.getPoint().y));
    BOOST_CHECK(std::isnan(compositeShape.getPoint().x));
  }

  BOOST_AUTO_TEST_CASE(TestMoveOnAxis)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.move(5, 4);
    pozdnova::point_t point = compositeShape.getPoint();

    BOOST_TEST(point.x == 8 + 5);
    BOOST_TEST(point.y == 7 + 4);
  }

  BOOST_AUTO_TEST_CASE(TestMoveOnAxisInEmptyCompositeShape)
  {
    pozdnova::CompositeShape compositeShape{};
    compositeShape.move(5, 4);

    BOOST_CHECK(std::isnan(compositeShape.getPoint().y));
    BOOST_CHECK(std::isnan(compositeShape.getPoint().x));
    BOOST_CHECK(std::isnan(compositeShape.getPoint().y));
    BOOST_CHECK(std::isnan(compositeShape.getPoint().x));
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.scale(5);
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_TEST(frame.pos.x == 8);
    BOOST_TEST(frame.pos.y == 7);
    BOOST_TEST(frame.width == 18 * 5);
    BOOST_TEST(frame.height == 18 * 5);
  }

  BOOST_AUTO_TEST_CASE(TestScaleAfterMoveToPoint)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.scale(3);
    compositeShape.move({5, 4});
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_TEST(frame.pos.x == 5);
    BOOST_TEST(frame.pos.y == 4);
    BOOST_TEST(frame.width == 18 * 3);
    BOOST_TEST(frame.height == 18 * 3);
  }

  BOOST_AUTO_TEST_CASE(TestScaleAfterMoveOnAxis)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    compositeShape.scale(3);
    compositeShape.move(5, 4);
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_TEST(frame.pos.x == 5 + 8);
    BOOST_TEST(frame.pos.y == 4 + 7);
    BOOST_TEST(frame.width == 18 * 3);
    BOOST_TEST(frame.height == 18 * 3);
  }

  BOOST_AUTO_TEST_CASE(TestScaleInEmptyCopmositeShape)
  {
    pozdnova::CompositeShape compositeShape{};

    compositeShape.scale(5);
    pozdnova::rectangle_t frame = compositeShape.getFrameRect();

    BOOST_CHECK(std::isnan(frame.pos.x));
    BOOST_CHECK(std::isnan(frame.pos.y));
    BOOST_TEST(frame.width == 0);
    BOOST_TEST(frame.height == 0);
  }

  BOOST_AUTO_TEST_CASE(TestOperatorOfIndexig)
  {
    pozdnova::CompositeShape compositeShape{};
    std::shared_ptr<pozdnova::Rectangle> rectangle = std::make_shared<pozdnova::Rectangle>(
      pozdnova::rectangle_t{9, 8, 7, 6});
    std::shared_ptr<pozdnova::Circle> circle1 = std::make_shared<pozdnova::Circle>(9, pozdnova::point_t{8, 7});
    std::shared_ptr<pozdnova::Circle> circle2 = std::make_shared<pozdnova::Circle>(9, pozdnova::point_t{8, 7});
    compositeShape.add(rectangle);
    compositeShape.add(circle1);
    compositeShape.add(circle2);

    BOOST_TEST(compositeShape[0] == rectangle);
    BOOST_TEST(compositeShape[1] == circle1);
    BOOST_TEST(compositeShape[2] == circle2);
  }

  BOOST_AUTO_TEST_CASE(TestAdd)
  {
    pozdnova::CompositeShape compositeShape{};
    std::shared_ptr<pozdnova::Rectangle> rectangle = std::make_shared<pozdnova::Rectangle>(
      pozdnova::rectangle_t{9, 8, 7, 6});
    std::shared_ptr<pozdnova::Circle> circle1 = std::make_shared<pozdnova::Circle>(9, pozdnova::point_t{8, 7});
    std::shared_ptr<pozdnova::Circle> circle2 = std::make_shared<pozdnova::Circle>(9, pozdnova::point_t{8, 7});
    size_t sizeBefore = compositeShape.size();

    compositeShape.add(rectangle);
    compositeShape.add(circle1);
    compositeShape.add(circle2);

    BOOST_TEST(sizeBefore + 3 == compositeShape.size());
  }

  BOOST_AUTO_TEST_CASE(TestAddWithNullPtr)
  {
    pozdnova::CompositeShape compositeShape{};
    BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
  };

  BOOST_AUTO_TEST_CASE(TestPopBack)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);
    size_t sizeBefore = compositeShape.size();

    compositeShape.remove();

    BOOST_TEST(sizeBefore == compositeShape.size() + 1);
  }

  BOOST_AUTO_TEST_CASE(TestEmpty)
  {
    pozdnova::CompositeShape filledCompasiteShape{};
    pozdnova::CompositeShape emptyCompasiteShape{};
    initializationOfCompositeShape(filledCompasiteShape);

    BOOST_TEST(filledCompasiteShape.empty() == false);
    BOOST_TEST(emptyCompasiteShape.empty() == true);
  }

  BOOST_AUTO_TEST_CASE(TestSize)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    BOOST_TEST(compositeShape.size() == 2);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeRatioValue)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    BOOST_CHECK_THROW(compositeShape.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroRatioValue)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    BOOST_CHECK_THROW(compositeShape.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestOutOfRangeIndex)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);

    BOOST_CHECK_THROW(compositeShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestEmptyCompositeShapeIndex)
  {
    pozdnova::CompositeShape compositeShape{};

    BOOST_CHECK_THROW(compositeShape[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestZeroValueAdd)
  {
    pozdnova::CompositeShape compositeShape{};

    BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestAssignmentOperator)
  {
    pozdnova::CompositeShape compositeShape{};
    pozdnova::CompositeShape compositeShapeForCoping;
    initializationOfCompositeShape(compositeShape);

    compositeShapeForCoping = compositeShape;

    BOOST_TEST(compositeShape[0] == compositeShapeForCoping[0]);
    BOOST_TEST(compositeShape[1] == compositeShapeForCoping[1]);
  }

  BOOST_AUTO_TEST_CASE(TestCopyConstructor)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);
    pozdnova::CompositeShape compositeShapeForCoping(compositeShape);

    BOOST_TEST(compositeShape[0] == compositeShapeForCoping[0]);
    BOOST_TEST(compositeShape[1] == compositeShapeForCoping[1]);
  }

  BOOST_AUTO_TEST_CASE(TestRotate)
  {
    pozdnova::CompositeShape testCompositeShape{};
    initializationOfCompositeShape(testCompositeShape);
    pozdnova::rectangle_t expectedFrameOfCompositeShape{18, 18, {8, 7}};

    testCompositeShape.rotate(45);

    BOOST_TEST(expectedFrameOfCompositeShape.width == testCompositeShape.getFrameRect().width);
    BOOST_TEST(expectedFrameOfCompositeShape.height == testCompositeShape.getFrameRect().height);
    BOOST_TEST(expectedFrameOfCompositeShape.pos.x == testCompositeShape.getFrameRect().pos.x);
    BOOST_TEST(expectedFrameOfCompositeShape.pos.y == testCompositeShape.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestRotateOn180Deg)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);
    pozdnova::rectangle_t expectedFrameOfCompositeShape{18, 18, {8, 7}};

    compositeShape.rotate(180);

    BOOST_TEST(expectedFrameOfCompositeShape.width == compositeShape.getFrameRect().width);
    BOOST_TEST(expectedFrameOfCompositeShape.height == compositeShape.getFrameRect().height);
    BOOST_TEST(expectedFrameOfCompositeShape.pos.x == compositeShape.getFrameRect().pos.x);
    BOOST_TEST(expectedFrameOfCompositeShape.pos.y == compositeShape.getFrameRect().pos.y);
  }



BOOST_AUTO_TEST_SUITE_END()
