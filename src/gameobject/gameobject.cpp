#include "gameobject.hpp"
#include <GL/gl.h>


GameObject::GameObject(Shape* shape): shape(shape) {};

GameObject::GameObject(Shape* shape, std::shared_ptr<GameObject> parent): shape(shape), parent(parent) {};

void GameObject::draw(){
  if(shape){
    shape->draw();
  }
}

void GameObject::pushTransform() const{
  glPushMatrix();
  glTranslatef(this->position.x, this->position.y, this->position.z);
  glRotatef(this->rotation.y, 0, 1, 0);
  glRotatef(this->rotation.x, 1, 0, 0);
  glRotatef(this->rotation.z, 0, 0, 1); 
  if(parent){
    parent->pushTransform();
  }
}

void GameObject::popTransform() const {
  glPopMatrix();
  if(parent){
    this->parent->popTransform();
  }
}

void GameObject::setParent(std::shared_ptr<GameObject> parent){
  this->parent = parent;
}
