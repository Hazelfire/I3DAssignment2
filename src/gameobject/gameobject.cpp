#include "gameobject.hpp"


GameObject::GameObject(Shape* shape): shape(shape) {};

GameObject::GameObject(Shape* shape, std::shared_ptr<GameObject> parent): shape(shape), parent(parent) {};

void GameObject::draw(){
  if(shape){
    shape->draw();
  }
}

Transform GameObject::getWorldTransform() const{
  Transform re;
  if(parent){
    Transform parentTrans = parent->getWorldTransform();
    v3d newPosition = v3d(this->position);
    newPosition.rotate(parentTrans.rotation.y, v3d::Y);
    newPosition.rotate(parentTrans.rotation.x, v3d::X);
    newPosition.rotate(parentTrans.rotation.z, v3d::Z);
    re.position = newPosition + parentTrans.position;
    re.rotation = this->rotation + parentTrans.rotation;
    return re;
  }  
  else {
    re.position = this->position;
    re.rotation = this->rotation;
  }
  return re;
}

void GameObject::setParent(std::shared_ptr<GameObject> parent){
  this->parent = parent;
}
