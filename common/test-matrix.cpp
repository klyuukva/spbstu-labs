#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <memory>

inline void initializationOfCompositeShape(pozdnova::CompositeShape& testCompositeShape)
{
  std::shared_ptr<pozdnova::Rectangle> rectangle = std::make_shared<pozdnova::Rectangle>(
    pozdnova::rectangle_t{9, 8, 7, 6});
  std::shared_ptr<pozdnova::Circle> circle = std::make_shared<pozdnova::Circle>(9, pozdnova::point_t{8, 7});
  testCompositeShape.add(rectangle);
  testCompositeShape.add(circle);
}

BOOST_AUTO_TEST_SUITE(TestMatrix, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestCreatMatrix)
  {
    BOOST_CHECK_NO_THROW(pozdnova::Matrix matrix);
  }

  BOOST_AUTO_TEST_CASE(TestMatrixSeparation)
  {
    pozdnova::CompositeShape shapes;
    initializationOfCompositeShape(shapes);

    pozdnova::Matrix matrix;
    matrix = matrix.layerFilling(shapes);
    BOOST_TEST(matrix[0][0]->getArea(), shapes[0]->getArea());
    BOOST_TEST(matrix[1][0]->getArea(), shapes[1]->getArea());
  }

  BOOST_AUTO_TEST_CASE(TestOutOfRangeIndex)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);
    pozdnova::Matrix matrix;
    matrix = matrix.layerFilling(compositeShape);

    BOOST_CHECK_THROW(matrix[3], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestNegativeIndex)
  {
    pozdnova::CompositeShape compositeShape{};
    initializationOfCompositeShape(compositeShape);
    pozdnova::Matrix matrix;
    matrix = matrix.layerFilling(compositeShape);

    BOOST_CHECK_THROW(matrix[-3], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
