#include "terrain.hpp"
#include "shape/primitives/primitives.hpp"


void create_terrain(Scene& scene){
  // Main grass
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -1.5, 0), v3d(10, 1, 5)))), "floor");

  // Road
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -1, 5), v3d(10, 1, 5)))), "floor");

  // Grass on other side
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -6, 10), v3d(10, 10, 5)))), "floor");

  // Bottom of lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -10, 15), v3d(10, 1, 5)))), "floor");

  // Grass on other side of lake
  scene.add(shared_ptr<GameObject>(new GameObject(new Cube(v3d(0, -6, 20), v3d(10, 10, 5)))), "floor");


}
