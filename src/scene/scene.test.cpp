#include <boost/test/unit_test.hpp>
#include "scene.hpp"
#include "vector/vector.h"
#include <cmath>
#include "shape/primitives/primitives.hpp"

class GameObjectMock : public GameObject {
  private:
    int drawCountCall = 0;
    Cube cube;
  public:
    GameObjectMock(): cube(Cube(v3d::zero, v3d::unit)), GameObject(new Cube(v3d::zero, v3d::unit)){}
    void draw(){ 
      drawCountCall++; 
    }
    int getDrawCountCall(){
      return drawCountCall;
    }
};

BOOST_AUTO_TEST_CASE( test_scene_draw )
/* Compare with void free_test_function() */
{
  Scene scene;
  GameObjectMock mock;
  mock.draw();
  scene.add(mock, "tag");

  BOOST_TEST(mock.getDrawCountCall() == 1);

  scene.draw();

  BOOST_TEST(scene.getObjectsByTag("none").size() == 0);
  BOOST_TEST(scene.getObjectsByTag("tag").size() == 1);

}
