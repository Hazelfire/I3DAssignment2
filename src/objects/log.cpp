#include "log.hpp"
#include <cmath>

Colour brown(0.3, 0.3, 0.2, 1);

  Log::Log(v3d position, GLuint texture, double speed): 
    GameObject(
        std::make_shared<Cylinder>(Material(0.6, brown*0.1, brown, brown, texture),v3d::zero, 0.5, 2 ), 
        std::make_shared<Cylinder>(Material(0.6, brown*0.1, brown, brown, texture),v3d::zero, 0.5, 2 )
        ), logSpeed(speed) {

  this->shape->material.texture = texture;
  this->position = position;
};

void Log::update(double dt){
  ((Cylinder*)collider.get())->position = this->position;
  position.x = fmod(( (position.x + 10) + dt * logSpeed) + 20, 20) - 10;
}

void Log::draw(DrawOptions opts) const {
  GameObject::draw(opts);
}
