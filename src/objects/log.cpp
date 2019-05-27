#include "log.hpp"
#include <cmath>

Colour brown(0.3, 0.3, 0.2, 1);

Log::Log(v3d position, GLuint texture): GameObject(new Cylinder(Material(0.6, brown*0.1, brown, brown, texture),v3d::zero, 0.5, 2 ), new Cylinder(Material(0.6, brown*0.1, brown, brown, texture),v3d::zero, 0.5, 2 )) {
  this->shape->material.texture = texture;
  this->position = position;
};

void Log::update(double dt){
  ((Cylinder*)collider.get())->position = this->position;
  const double logSpeed = 2;
  position.x = fmod(( (position.x + 5) + dt * logSpeed), 10) - 5;
}

void Log::draw(DrawOptions opts){
  GameObject::draw(opts);
}
