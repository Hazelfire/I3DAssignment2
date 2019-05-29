#include <boost/test/unit_test.hpp>
#include "primitives.hpp"

BOOST_AUTO_TEST_CASE( test_sphere_collision )
{
  Sphere s1(v3d::zero, 2);
  Sphere s2(v3d(0, 4, 0), 1);
  BOOST_TEST(s1.distance(s2) == 1.0);
  BOOST_TEST(!s1.collidesWith(s2));
  s2.position = v3d(0, 2.5, 0);
  BOOST_TEST(s1.collidesWith(s2));
}


BOOST_AUTO_TEST_CASE( test_sphere_plane )
{
  Sphere sphere(v3d(0, 2, 0), 1);
  Grid plane(0);
  BOOST_TEST(!sphere.collidesWith(plane));
  BOOST_TEST(!plane.collidesWith(sphere));
  plane.height = 1.5;

  BOOST_TEST(sphere.collidesWith(plane));
  BOOST_TEST(plane.collidesWith(sphere));
}

BOOST_AUTO_TEST_CASE( test_sphere_cube )
{
  Cube cube(v3d::zero, v3d::unit);
  Sphere sphere(v3d(0, 2, 0), 1);

  BOOST_TEST(!cube.collidesWith(sphere));
  BOOST_TEST(!sphere.collidesWith(cube));

  sphere.position.y = 1.1;

  BOOST_TEST(cube.collidesWith(sphere));
  BOOST_TEST(sphere.collidesWith(cube));

}

BOOST_AUTO_TEST_CASE( test_sphere_cylinder )
{
  Sphere sphere(v3d(0, 2.5, 0), 1);
  Cylinder cylinder(v3d(0, 0, 0), 1, 3);

  BOOST_TEST(!cylinder.collidesWith(sphere));
  BOOST_TEST(!sphere.collidesWith(cylinder));

  sphere.position.y = 1.5;

  BOOST_TEST(cylinder.collidesWith(sphere));
  BOOST_TEST(sphere.collidesWith(cylinder));
}

BOOST_AUTO_TEST_CASE( test_cube_cube )
{
  Cube c1(v3d::zero, v3d::unit);
  Cube c2(v3d(0, 2, 0), v3d::unit);

  BOOST_TEST(!c1.collidesWith(c2));
  BOOST_TEST(!c2.collidesWith(c1));

  c2.position.y = 0.5;

  BOOST_TEST(c1.collidesWith(c2));
  BOOST_TEST(c2.collidesWith(c1));

}

BOOST_AUTO_TEST_CASE( test_cube_sphere )
{
  Cube c1(v3d(0, 1, 0), v3d::unit);
  Grid p1(0);

  BOOST_TEST(!c1.collidesWith(p1));
  BOOST_TEST(!p1.collidesWith(c1));

  c1.position.y = 0.1;

  BOOST_TEST(c1.collidesWith(p1));
  BOOST_TEST(p1.collidesWith(c1));

}

BOOST_AUTO_TEST_CASE ( test_cube_cylinder )
{
  Cube cube(v3d(0, 2, 0), v3d::unit);
  Cylinder cylinder(v3d::zero, 1, 2);

  BOOST_TEST(!cube.collidesWith(cylinder));
  BOOST_TEST(!cylinder.collidesWith(cube));

  cube.position.y = 1.1;

  BOOST_TEST(cube.collidesWith(cylinder));
  BOOST_TEST(cylinder.collidesWith(cube));
}

BOOST_AUTO_TEST_CASE (test_plane_plane)
{
  Grid p1(2.0);
  Grid p2(1.0);

  BOOST_TEST(!p1.collidesWith(p2));
  BOOST_TEST(!p2.collidesWith(p1));

  p2.height = 2.0;

  BOOST_TEST(p1.collidesWith(p2));
  BOOST_TEST(p2.collidesWith(p1));
}

BOOST_AUTO_TEST_CASE (test_plane_cylinder)
{
  Grid p1(0);
  Cylinder cylinder(v3d(0, 2, 0), 1, 2);

  BOOST_TEST(!p1.collidesWith(cylinder));
  BOOST_TEST(!cylinder.collidesWith(p1));

  cylinder.position.y = 0.9;

  BOOST_TEST(p1.collidesWith(cylinder));
  BOOST_TEST(cylinder.collidesWith(p1));
}


BOOST_AUTO_TEST_CASE (test_cylinder_cylinder)
{
  Cylinder c1(v3d::zero, 1, 2);
  Cylinder c2(v3d(0, 2.5, 0), 1, 2);

  BOOST_TEST(!c1.collidesWith(c2));
  BOOST_TEST(!c2.collidesWith(c1));

  c2.position.y = 1.5;

  BOOST_TEST(c1.collidesWith(c2));
  BOOST_TEST(c2.collidesWith(c1));
}
