#include "gameobject.h"


GameObject::GameObject(Shape& shape): shape(shape) {};

void GameObject::draw(){
  shape.draw();
}

