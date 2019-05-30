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


/*
template <typename anim_id>
bool animated_gameobject<anim_id>::animation::operator<(const animation& r) const {
  return name < r.name;
}
*/

template <typename anim_id>
animated_gameobject<anim_id>::animation::keyframe::keyframe(
    const v3d &position, 
    const v3d &rotation, 
    double time_offset
    ): position(position), rotation(rotation), time_offset(time_offset) 
{
}

template <typename anim_id>
bool animated_gameobject<anim_id>::play(anim_id to_play) {
  auto anim = animations.find(to_play);
  if(!anim) {
    playing = nullptr;
    return false;
  }
  playing = &*anim;
  orig_position = position;
  orig_rotation = rotation;
  playing_duration = 0;
  anim->next_frame = 0;
  return true;
}

template <typename anim_id>
void animated_gameobject<anim_id>::update(double dt) {
  if(playing) {
    //TODO
    playing_duration += dt;
    if(playing->next_frame < playing->frames.size()) {
      if(playing_duration > playing->frames[playing->next_frame]) {
        playing->next_frame++;
      }
    }

    if(playing->next_frame == 0) {
      // interp between orig_pos and keyframe
      double between_frames = playing->frames[playing->next_frame].time_offset;
      double prv_percent = playing_duration / between_frames;
      double nxt_percent = (playing->frames[playing->next_frame].time_offset - playing_duration) / between_frames;

      position = orig_position * prv_percent + playing->frames[playing->next_frame].position * nxt_percent;
      rotation = orig_rotation * prv_percent + playing->frames[playing->next_frame].rotation * nxt_percent;
    } else if(playing->next_frame < playing->frames.size()) {
      // interp between keyframe and keyframe
      double between_frames = playing->frames[playing->next_frame].time_offset - playing->frames[playing->next_frame-1].time_offset;
      double prv_percent = (playing_duration - playing->frames[playing->next_frame-1].time_offset) / between_frames;
      double nxt_percent = (playing->frames[playing->next_frame].time_offset - playing_duration) / between_frames;

      position = playing->frames[playing->next_frame-1].position * prv_percent + playing->frames[playing->next_frame].position * nxt_percent;
      rotation = playing->frames[playing->next_frame-1].rotation * prv_percent + playing->frames[playing->next_frame].rotation * nxt_percent;
    } else {
      // back to orig_pos
      position = orig_position;
      rotation = orig_rotation;
    }
  }
}

