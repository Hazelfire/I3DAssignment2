#include "terrain.hpp"
#include "shape/primitives/primitives.hpp"
#include "shape/primitives/function/function.hpp"
#include "objects/car.hpp"
#include "objects/log.hpp"


void create_terrain(Scene& scene){
  // Main grass
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -1.5, 0), v3d(10, 1, 5)))), "floor");

  // Road
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -1, 5), v3d(10, 1, 5)))), "floor");

  // cars
  scene.add(shared_ptr<GameObject>(new Car(v3d(-3, 0.5, 3.5))), "death");
  scene.add(shared_ptr<GameObject>(new Car(v3d(0, 0.5, 5))), "death");
  scene.add(shared_ptr<GameObject>(new Car(v3d(3, 0.5, 6.5))), "death");

  // Grass on other side
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -6, 10), v3d(10, 10, 5)))), "floor");

  // Bottom of lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -10, 15), v3d(10, 1, 5)))), "floor");

  // Grass on other side of lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -6, 20), v3d(10, 10, 5)))), "floor");

  // water in lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Tute_Water(v3d(0, -2, 15), v3d(10, 0.5, 5)))), "floor");

  // Logs
  scene.add(shared_ptr<GameObject>(new Log(v3d(-3, 0.5, 13.5))), "log");
  scene.add(shared_ptr<GameObject>(new Log(v3d(0, 0.5, 15))), "log");
  scene.add(shared_ptr<GameObject>(new Log(v3d(3, 0.5, 16.5))), "log");



}
