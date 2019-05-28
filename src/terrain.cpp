#include "terrain.hpp"
#include "shape/primitives/primitives.hpp"
#include "shape/primitives/function/function.hpp"
#include "material/material.hpp"
#include "objects/car.hpp"
#include "objects/log.hpp"
#include <SOIL.h>

using namespace std;

void create_terrain(Scene& scene){
  Colour white_specular(1, 1, 1, 1);
  Colour no_specular(0, 0, 0, 0);
  float ambient_scale = 0.4;

  //Colour green(0.05, 0.4, 0.05, 1);
  Colour green(0.14509, 0.3, 0.08627, 1);
  Material grassMaterial(128, green * ambient_scale, green, white_specular);
  // Main grass

  scene.add(std::make_shared<GameObject>(std::make_shared<Cube>(grassMaterial, v3d(0, -1.5, 0), v3d(10, 1, 5))), tag::floor);

  Colour grey(0.1, 0.1, 0.1, 1);
  Material roadMaterial(128, grey * ambient_scale, grey, white_specular * 0.1);
  // Road
  scene.add(std::make_shared<GameObject>(std::make_shared<Cube>(roadMaterial, v3d(0, -1, 5), v3d(10, 1, 5))), tag::floor);

  // cars
  scene.add(std::make_shared<Car>(v3d(-3, 0, 1.5)), tag::death);
  scene.add(std::make_shared<Car>(v3d(0, 0, 2.5)), tag::death);
  scene.add(std::make_shared<Car>(v3d(3, 0, 3.5)), tag::death);

  // Grass on other side
  scene.add(std::make_shared<GameObject>(std::make_shared<Cube>(grassMaterial, v3d(0, -6, 10), v3d(10, 10, 5))), tag::floor);

  // Bottom of lake
  scene.add(std::make_shared<GameObject>(std::make_shared<Cube>(grassMaterial, v3d(0, -10, 15), v3d(10, 1, 5))), tag::floor);

  // Grass on other side of lake
  scene.add(std::make_shared<GameObject>(std::make_shared<Cube>(grassMaterial, v3d(0, -6, 20), v3d(10, 10, 5))), tag::floor);

  // water in lake
  Colour blue(0, 0.2, 1, 0.5);
  Material waterMaterial(128, blue * ambient_scale, blue, white_specular);
  scene.add(std::make_shared<GameObject>(std::make_shared<Tute_Water>(waterMaterial, v3d(0, -2, 15), v3d(10, 0.5, 5))), tag::floor);

  // Logs
  GLuint texture = SOIL_load_OGL_texture("resources/wood.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  scene.add(std::make_shared<Log>(v3d(-3, -0.5, 6.5), texture), tag::log);
  scene.add(std::make_shared<Log>(v3d(0, -0.5, 7.5), texture), tag::log);
  scene.add(std::make_shared<Log>(v3d(3, -0.5, 8.5), texture), tag::log);



}
