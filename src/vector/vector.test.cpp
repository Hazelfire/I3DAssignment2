#include <boost/test/unit_test.hpp>
#include "vector.h"
#include <cmath>

BOOST_AUTO_TEST_CASE( test_distance )
/* Compare with void free_test_function() */
{
  BOOST_TEST( v3d::zero.distance(v3d::X) == 1.0);
  BOOST_TEST( v3d::zero.distance(v3d::unit) == sqrt(3) );
}
