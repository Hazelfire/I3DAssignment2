#include "animated_gameobject.hpp"

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

