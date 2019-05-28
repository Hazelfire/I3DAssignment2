#include "gameobject.hpp"
#include <GL/gl.h>


GameObject::GameObject(Shape* shape): shape(shape) {};

GameObject::GameObject(Shape* shape, std::shared_ptr<GameObject> parent): shape(shape) {
  // need to use the method here, so that we get added to the parents children
  setParent(parent);
};

GameObject::GameObject(const GameObject& other): parent(other.parent), position(other.position), rotation(other.rotation) {
  // TODO make shape a unique_ptr instead
  shape.reset(other.shape->clone().get());
  std::shared_ptr<GameObject> parent(other.parent);
  setParent(parent);
}

void GameObject::draw(DrawOptions ops){
  if(shape){
    this->pushTransform();
    shape->draw(ops);
    for(auto child : children) {
      child->draw(ops);
    }
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

  std::shared_ptr<GameObject> parent = this->parent.lock();
  if(parent){
    parent->pushTransform();
  }
}

void GameObject::popTransform() const {
  glPopMatrix();
  std::shared_ptr<GameObject> parent = this->parent.lock();
  if(parent){
    parent->popTransform();
  }
}

void GameObject::setParent(std::shared_ptr<GameObject> new_parent){
  // makes sure we don't get deleted during this function
  std::shared_ptr<GameObject> self = this->self.lock();

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
