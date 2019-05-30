#include "animated_gameobject.hpp"


template <typename anim_id>
animated_gameobject<anim_id>::animated_gameobject():
      animated_gameobject(nullptr, nullptr) {};
template <typename anim_id>
animated_gameobject<anim_id>::animated_gameobject(std::shared_ptr<Shape> shape):
      animated_gameobject(shape, nullptr) {};
template <typename anim_id>
animated_gameobject<anim_id>::animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider):
      GameObject(shape, collider), playing(nullptr) {};
template <typename anim_id>


animated_gameobject<anim_id>::animated_gameobject(std::unique_ptr<std::set<animation>> &&anims):
      animated_gameobject(nullptr, nullptr, anims) {};
template <typename anim_id>
animated_gameobject<anim_id>::animated_gameobject(std::shared_ptr<Shape> shape, std::unique_ptr<std::set<animation>> &&anims):
      animated_gameobject(shape, nullptr, anims) {};
template <typename anim_id>
animated_gameobject<anim_id>::animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider, std::unique_ptr<std::set<animation>> &&anims):
      GameObject(shape, collider), animations(*anims.release()) {};


template <typename anim_id>
bool animated_gameobject<anim_id>::animation::operator<(const animation& r) const {
  return name < r.name;
}

template <typename anim_id>
animated_gameobject<anim_id>::animation::keyframe::keyframe(
    const v3d &position, 
    const v3d &rotation, 
    double time_offset
    ): position(position), rotation(rotation), time_offset(time_offset) 
{
}

/*
void animated_gameobject::draw(DrawOptions ops){
  this->pushRelativeTransform();

  if(shape)
    shape->draw(ops);

  for(auto child : children) {
    child->draw(ops);
  }

  this->popRelativeTransform();
  if(ops.collider && collider){
    collider->draw(ops);
  }
}
*/
