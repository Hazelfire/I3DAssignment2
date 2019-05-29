#include "gameobject.hpp"
#include <GL/gl.h>


GameObject::GameObject(): shape(nullptr), collider(nullptr), position(v3d::zero), rotation(v3d::zero) {};
GameObject::GameObject(std::shared_ptr<Shape> shape): shape(shape), collider(nullptr), position(v3d::zero), rotation(v3d::zero) {};
GameObject::GameObject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider): shape(shape), collider(collider), position(v3d::zero), rotation(v3d::zero) {};

GameObject::GameObject(const GameObject& other): enable_shared_from_this<GameObject>(other), parent(other.parent), children(other.children), shape(nullptr), collider(nullptr), position(other.position), rotation(other.rotation) {
  // TODO make shape a unique_ptr instead
  if(other.shape) {
    shape.reset(other.shape->clone().release());
  }
  if(other.collider) {
    collider.reset(other.collider->clone().release());
  }
}

bool GameObject::collidesWith(const GameObject &other) const {
  bool collides = collider->collidesWith(*other.collider);
  return collides;
}

std::shared_ptr<GameObject> GameObject::clone() const {
  return clone(this->parent.lock());
}

std::shared_ptr<GameObject> GameObject::clone(std::shared_ptr<GameObject> new_parent) const {
  auto temp = std::shared_ptr<GameObject>(new GameObject(*this));

  if(new_parent) {
    temp->parent = new_parent;
    new_parent->children.insert(temp);
    //parent->children.push_back(temp);
  }

  for(auto object_sp : temp->children) {
    //don't set the sp while its in the set, that invalidates the set
    //  since thats how it detects dupes
    //object_sp = object_sp->clone(temp);
    temp->children.erase(object_sp);
    object_sp->clone(temp);
  }

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

    if(new_parent == parent)
      return;

    if(parent){
      parent->children.erase(parent->children.find(self));
#if 0
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
#endif
    }
  }

  if(new_parent) {
    //new_parent->children.push_back(self);
    new_parent->children.insert(self);
    parent = new_parent;
  }
}

void GameObject::update(double dt) {
  if(shape) shape->update(dt);
    for(auto child : children) {
      child->update(dt);
    }
}
