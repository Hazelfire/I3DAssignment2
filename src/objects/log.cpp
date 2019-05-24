#include "log.hpp"
#include <cmath>

Log::Log(v3d position): GameObject(new Cylinder(v3d::zero, 0.5, 2 )) {
  this->position = position;
};

void Log::update(double dt){
  const double logSpeed = 2;
  position.x = fmod(( (position.x + 5) + dt * logSpeed), 10) - 5;
}

void Log::draw(DrawOptions opts){
  this->pushTransform();
  GameObject::draw(opts);
  this->popTransform();
}
