#include "gameobject.hpp"
#include <GL/gl.h>


GameObject::GameObject(std::shared_ptr<Shape> shape): shape(shape), position(v3d::zero), rotation(v3d::zero) {};


GameObject::GameObject(const GameObject& other): enable_shared_from_this<GameObject>(other), parent(other.parent), position(other.position), rotation(other.rotation) {
  // TODO make shape a unique_ptr instead
  shape.reset(other.shape->clone().release());
  /*
  std::shared_ptr<GameObject> parent = other.parent.lock();

  setParent(parent);
  */
}

std::shared_ptr<GameObject> GameObject::clone() const {
  auto temp = std::shared_ptr<GameObject>(new GameObject(*this));

  std::shared_ptr<GameObject> parent = this->parent.lock();
  temp->setParent(parent);
  return temp;
}

void GameObject::draw(DrawOptions ops){
  this->pushRelativeTransform();

  if(shape)
    shape->draw(ops);

  for(auto child : children) {
    child->draw(ops);
  }
  this->popRelativeTransform();
}

void GameObject::pushTransform() const{
  pushRelativeTransform();

  std::shared_ptr<GameObject> parent = this->parent.lock();
  if(parent){
    parent->pushTransform();
  }
}

void GameObject::pushRelativeTransform() const {
  glPushMatrix();
  glRotatef(this->rotation.y, 0, 1, 0);
  v3d right = v3d(0, 0, 1).rotate(this->rotation.y, v3d::Y).cross(v3d::Y);
  glRotatef(this->rotation.x, right);
  glRotatef(this->rotation.z, 0, 0, 1); 
  glTranslatef(position);
}

void GameObject::popTransform() const {
  std::shared_ptr<GameObject> parent = this->parent.lock();
  if(parent){
    parent->popTransform();
  }

  popRelativeTransform();
}

void GameObject::popRelativeTransform() const {
  glPopMatrix();
}

void GameObject::setParent(std::shared_ptr<GameObject> new_parent){
  // makes sure we don't get deleted during this function
  std::shared_ptr<GameObject> self = shared_from_this();

  {
    std::shared_ptr<GameObject> parent = this->parent.lock();
    if(parent){
      // remove ourselfves from our parents list of children
      // swaps our position to the end, then pops the end
      // this is ok, because the list of children has no inherent order
      // maybe use a set to get O(log(n)) behavior some time later
      //for(std::vector<std::shared_ptr<GameObject>>::iterator child_sp_it = parent->children.begin(); child_sp_it != parent->children.end(); child_sp_it++) {
      for(auto child_sp_it : parent->children) {
        if(child_sp_it == self) {
          child_sp_it.swap(parent->children.back());
          parent->children.pop_back();
          break;
        }
      }
    }
  }

  if(new_parent) {
    new_parent->children.push_back(self);
    parent = new_parent;
  }
}

void GameObject::update(double dt) {
  if(shape) shape->update(dt);
    for(auto child : children) {
      child->update(dt);
    }
}
