#include "log.hpp"
#include <cmath>

Log::Log(v3d position): GameObject(new Cylinder(position, 1, 2 )) {};

void Log::update(double dt){
  const double logSpeed = 2;
  t += dt;
  position.x = fmod(( t * logSpeed), 10) - 5;
}

void Log::draw(){
  this->pushTransform();
  GameObject::draw();
  this->popTransform();
}
