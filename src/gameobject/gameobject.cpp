#include "gameobject.hpp"
#include <GL/gl.h>
#include <iostream>


GameObject::GameObject(Shape* shape): shape(shape), collider(shape) {};
GameObject::GameObject(Shape* shape, Shape* collider): shape(shape), collider(collider) {};


GameObject::GameObject(Shape* shape, std::shared_ptr<GameObject> parent): shape(shape), parent(parent), collider(shape) {};

bool GameObject::collidesWith(const GameObject &other) const {
  bool collides = collider->collidesWith(*other.collider);
  return collides;
}

void GameObject::draw(DrawOptions ops){
  if(shape){
    this->pushTransform();
    shape->draw(ops);
    this->popTransform();
  }
}

void GameObject::pushTransform() const{
  glPushMatrix();
  glRotatef(this->rotation.y, 0, 1, 0);
  v3d right = v3d(0, 0, 1).rotate(this->rotation.y, v3d::Y).cross(v3d::Y);
  glRotatef(this->rotation.x, right);
  glRotatef(this->rotation.z, 0, 0, 1); 
  glTranslatef(position);
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

void GameObject::update(double dt) {
  if(shape) shape->update(dt);
}
