#include <boost/test/unit_test.hpp>
#include "polygon.hpp"
#include <cmath>

BOOST_AUTO_TEST_SUITE(TestPolygon, * boost::unit_test::tolerance(0.0001))

BOOST_AUTO_TEST_CASE(TestIsConvex)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {4, 1}, {5, 6}, {2, 7}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  BOOST_CHECK_NO_THROW(pozdnova::Polygon(points, size));
  }

BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);
  double correctArea = 4;

  double area = polygon.getArea();

  BOOST_TEST(correctArea == area);
  }

BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveToPoint)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  double area = polygon.getArea();
  polygon.move({ 5, 4 });
  double movedArea = polygon.getArea();

  BOOST_TEST(area == movedArea);
  }

BOOST_AUTO_TEST_CASE(TestUnalteredAreaAfterMoveOnAxis)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  double area = polygon.getArea();
  polygon.move(5, 4);
  double movedArea = polygon.getArea();

  BOOST_TEST(area == movedArea);
  }

BOOST_AUTO_TEST_CASE(TestMoveToPoint)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  polygon.move({ 5, 4 });
  pozdnova::rectangle_t frame = polygon.getFrameRect();

  BOOST_TEST(frame.pos.x == 5);
  BOOST_TEST(frame.pos.y == 4);
  }

BOOST_AUTO_TEST_CASE(TestMoveOnAxis)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  polygon.move(5, 4);
  pozdnova::rectangle_t frame = polygon.getFrameRect();

  BOOST_TEST(frame.pos.x == 7);
  BOOST_TEST(frame.pos.y == 6);
  }

BOOST_AUTO_TEST_CASE(TestGetFrameRect)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  pozdnova::rectangle_t frame = polygon.getFrameRect();

  BOOST_TEST(frame.pos.x == 2);
  BOOST_TEST(frame.pos.y == 2);
  BOOST_TEST(frame.width == 2);
  BOOST_TEST(frame.height == 2);
  }

BOOST_AUTO_TEST_CASE(TestScale)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  polygon.scale(5);
  pozdnova::rectangle_t frame = polygon.getFrameRect();

  BOOST_TEST(frame.pos.x == 2);
  BOOST_TEST(frame.pos.y == 2);
  BOOST_TEST(frame.width == 2 * 5);
  BOOST_TEST(frame.height == 2 * 5);
  }

BOOST_AUTO_TEST_CASE(TestScaleWithNegativeRatioValue)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);

  BOOST_CHECK_THROW(polygon.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_CASE(TestScaleWithZeroRatioValue)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{1, 1}, {1, 3}, {3, 3}, {3, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);
  BOOST_CHECK_THROW(polygon.scale(0), std::invalid_argument);
  }

BOOST_AUTO_TEST_CASE(TestRotate)
  {
    pozdnova::point_t points[] = {
    pozdnova::point_t{0, 0}, {1, 0}, {1, 1}, {0, 1}
  };
  const std::size_t size = sizeof(points) / sizeof(points[0]);
  pozdnova::Polygon polygon(points, size);
  pozdnova::rectangle_t frameBefore = polygon.getFrameRect();
  double areaBeforeRotate = polygon.getArea();
  double expectedFrameWidth = frameBefore.width / std::sqrt(2) + frameBefore.height / std::sqrt(2);
  double expectedFrameHeight = frameBefore.width / std::sqrt(2) + frameBefore.height / std::sqrt(2);

  polygon.rotate(45);

  pozdnova::rectangle_t frameAfterRotate = polygon.getFrameRect();
  double areaAfterRotate = polygon.getArea();

  BOOST_TEST(frameAfterRotate.pos.x == 0.5);
  BOOST_TEST(frameAfterRotate.pos.y == 0.5);
  BOOST_TEST(expectedFrameWidth == frameAfterRotate.width);
  BOOST_TEST(expectedFrameHeight == frameAfterRotate.height);
  BOOST_TEST(areaBeforeRotate == areaAfterRotate);

  }

BOOST_AUTO_TEST_SUITE_END()
