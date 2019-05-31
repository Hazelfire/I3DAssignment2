#include "animated_gameobject.hpp"

animated_gameobject::animated_gameobject():
      animated_gameobject(nullptr, (std::shared_ptr<Shape>)nullptr) {};
animated_gameobject::animated_gameobject(std::shared_ptr<Shape> shape):
      animated_gameobject(shape, (std::shared_ptr<Shape>)nullptr) {};
animated_gameobject::animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider):
      GameObject(shape, collider), playing(nullptr) {};


animated_gameobject::animated_gameobject(std::unique_ptr<std::map<anim::anim, animation>> anims):
      animated_gameobject(nullptr, nullptr, std::move(anims)) {};
animated_gameobject::animated_gameobject(std::shared_ptr<Shape> shape, std::unique_ptr<std::map<anim::anim, animation>> anims):
      animated_gameobject(shape, nullptr, std::move(anims)) {};
animated_gameobject::animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider, std::unique_ptr<std::map<anim::anim, animation>> anims):
      GameObject(shape, collider), animations(*anims.release()) {};


animated_gameobject::animation::keyframe::keyframe(
    const v3d &position, 
    const v3d &rotation, 
    double time_offset
    ): position(position), rotation(rotation), time_offset(time_offset) 
{
}


bool animated_gameobject::play(anim::anim to_play) {
  auto anim = animations.find(to_play);
  if(anim == animations.end()) {
    playing = nullptr;
    return false;
  }
  playing = &anim->second;
  orig_position = position;
  orig_rotation = rotation;
  playing_duration = 0;
  anim->second.next_frame = 0;
  return true;
}

bool animated_gameobject::recursive_play(anim::anim to_play) {
  // stack so we can recursively tell it to play
  std::vector<std::shared_ptr<GameObject>> to_update;
  // init the stack
  to_update.push_back(shared_from_this());

  bool has_any_played = false;
  while(!to_update.empty()) {
    std::shared_ptr<GameObject> current = to_update.back();
    to_update.pop_back();
    if(auto current_anim = dynamic_cast<animated_gameobject*>(current.get())) {
      has_any_played = has_any_played || current_anim->play(to_play);
    }

    for(std::set<std::shared_ptr<GameObject>>::iterator child = current->children.begin(); child != current->children.end(); child++) {
      to_update.push_back(*child);
    }
  }
  return has_any_played;
}


void animated_gameobject::update(double dt) {
  if(playing) {
    //TODO
    playing_duration += dt;
    if(playing->next_frame < playing->frames.size()) {
      if(playing_duration > playing->frames[playing->next_frame].time_offset) {
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
  GameObject::update(dt);
}

