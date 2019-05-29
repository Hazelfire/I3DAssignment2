#include "car.hpp"
#include <cmath>

Colour red(1, 0, 0, 1);
Car::Car(v3d position, double speed): GameObject(new Cube(Material(1, red, red, red), v3d::zero, v3d(2, 1, 1)), new Cube(Material(1, red, red, red), v3d::zero, v3d(2, 1, 1))), carSpeed(speed) {
  this->position = position;
};

void Car::update(double dt){
  ((Cube*)collider.get())->position = this->position;
  position.x = fmod(( (position.x + 5 ) + dt * carSpeed) + 10, 10) - 5;
}

void Car::draw(DrawOptions opts){
  GameObject::draw(opts);
}
