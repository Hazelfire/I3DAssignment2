#include "gameobject.hpp"


GameObject::GameObject(Shape* shape): shape(shape) {};

void GameObject::draw(){
  shape->draw();
}

