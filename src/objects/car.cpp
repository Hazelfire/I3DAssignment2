#include "car.hpp"
#include <cmath>

Colour red(1, 0, 0, 1);
Car::Car(v3d position): GameObject(std::make_shared<Cube>(Material(1, red, red, red), v3d::zero, v3d(2, 1, 1))) {
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
