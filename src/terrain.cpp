#include "terrain.hpp"
#include "shape/primitives/primitives.hpp"
#include "shape/primitives/function/function.hpp"
#include "material/material.hpp"
#include "objects/car.hpp"
#include "objects/log.hpp"
#include <SOIL.h>
#include <cstdlib>
#include <ctime>


void create_terrain() {
  Colour white_specular(1, 1, 1, 1);
  Colour no_specular(0, 0, 0, 0);
  float ambient_scale = 0.4;

  srand(time(0));

  //Colour green(0.05, 0.4, 0.05, 1);
  Colour green(0.14509, 0.3, 0.08627, 1);
  Material grassMaterial(128, green * ambient_scale, green, white_specular);
  // Main grass
  Scene::add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -1.5, 0), v3d(10, 1, 5)))), tag::floor);

  Colour grey(0.1, 0.1, 0.1, 1);
  Material roadMaterial(128, grey * ambient_scale, grey, white_specular * 0.1);
  // Road
  Scene::add(shared_ptr<GameObject>(new GameObject(new Cube(roadMaterial, v3d(0, -1, 6), v3d(10, 1, 7)))), tag::floor);

  // cars
  Scene::add(shared_ptr<GameObject>(new Car(v3d((rand() % 13) - 6, 0, 3), 2)), tag::death);
  Scene::add(shared_ptr<GameObject>(new Car(v3d((rand() % 13) - 6, 0, 5), -2)), tag::death);
  Scene::add(shared_ptr<GameObject>(new Car(v3d((rand() % 13) - 6, 0, 7), 2)), tag::death);
  Scene::add(shared_ptr<GameObject>(new Car(v3d((rand() % 13) - 6, 0, 9), -2)), tag::death);

  // Grass on other side
  Scene::add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -6, 12), v3d(10, 10, 5)))), tag::floor);

  // Bottom of lake
  Scene::add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -10, 17), v3d(10, 1, 5)))), tag::floor);

  // Grass on other side of lake
  Scene::add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -6, 24), v3d(10, 10, 5)))), tag::floor);

  // water in lake
  Colour blue(0, 0.2, 1, 0.5);
  Material waterMaterial(128, blue * ambient_scale, blue, white_specular);
  Scene::add(shared_ptr<GameObject>(new GameObject(new Tute_Water(waterMaterial, v3d(0, -2, 18), v3d(10, 0.5, 7)))), tag::death);

  // Logs
  GLuint texture = SOIL_load_OGL_texture("resources/wood.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  Scene::add(shared_ptr<GameObject>(new Log(v3d((rand() % 13) - 6, -0.5, 15), texture, 2)), tag::log);
  Scene::add(shared_ptr<GameObject>(new Log(v3d((rand() % 13) - 6, -0.5, 17), texture, -2)), tag::log);
  Scene::add(shared_ptr<GameObject>(new Log(v3d((rand() % 13) - 6, -0.5, 19), texture, 2)), tag::log);
  Scene::add(shared_ptr<GameObject>(new Log(v3d((rand() % 13) - 6, -0.5, 21), texture, -2)), tag::log);

}
