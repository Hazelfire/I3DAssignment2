#include "car.hpp"
#include <cmath>

Car::Car(v3d position): GameObject(new Cube(v3d::zero, v3d(2, 1, 1))) {
  this->position = position;
};

void Car::update(double dt){
  const double carSpeed = 2;
  position.x = fmod(( (position.x + 5) + dt * carSpeed), 10) - 5;
}

void Car::draw(DrawOptions opts){
  this->pushTransform();
  GameObject::draw(opts);
  this->popTransform();
}
