#include "car.hpp"
#include <cmath>

Car::Car(v3d position): GameObject(new Cube(position, v3d(2, 1, 1))) {};

void Car::update(double dt){
  const double carSpeed = 2;
  t += dt;
  position.x = fmod(( t * carSpeed), 10) - 5;
}

void Car::draw(){
  this->pushTransform();
  GameObject::draw();
  this->popTransform();
}
