#include "terrain.hpp"
#include "shape/primitives/primitives.hpp"
#include "shape/primitives/function/function.hpp"
#include "material/material.hpp"
#include "objects/car.hpp"
#include "objects/log.hpp"
#include <SOIL.h>


void create_terrain(Scene& scene){
  Colour white_specular(1, 1, 1, 1);

  Colour green(0, 1, 0, 1);
  Material grassMaterial(0.2, green * 0.1, green, white_specular);
  // Main grass
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -1.5, 0), v3d(10, 1, 5)))), tag::floor);

  Colour grey(0.1, 0.1, 0.1, 1);
  Material roadMaterial(0.3, grey * 0.1, grey, white_specular);
  // Road
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(roadMaterial, v3d(0, -1, 5), v3d(10, 1, 5)))), tag::floor);

  // cars
  scene.add(shared_ptr<GameObject>(new Car(v3d(-3, 0, 1.5))), tag::death);
  scene.add(shared_ptr<GameObject>(new Car(v3d(0, 0, 2.5))), tag::death);
  scene.add(shared_ptr<GameObject>(new Car(v3d(3, 0, 3.5))), tag::death);

  // Grass on other side
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -6, 10), v3d(10, 10, 5)))), tag::floor);

  // Bottom of lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -10, 15), v3d(10, 1, 5)))), tag::floor);

  // Grass on other side of lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(grassMaterial, v3d(0, -6, 20), v3d(10, 10, 5)))), tag::floor);

  // water in lake
  Colour blue(0, 1, 0, 0.5);
  Material waterMaterial(0.5, blue * 0.1, blue, white_specular);
  scene.add(shared_ptr<GameObject>(new GameObject(new Tute_Water(waterMaterial, v3d(0, -2, 15), v3d(10, 0.5, 5)))), tag::floor);

  // Logs
  GLuint texture = SOIL_load_OGL_texture("resources/wood.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  scene.add(shared_ptr<GameObject>(new Log(v3d(-3, -0.5, 6.5), texture)), tag::log);
  scene.add(shared_ptr<GameObject>(new Log(v3d(0, -0.5, 7.5), texture)), tag::log);
  scene.add(shared_ptr<GameObject>(new Log(v3d(3, -0.5, 8.5), texture)), tag::log);



}
