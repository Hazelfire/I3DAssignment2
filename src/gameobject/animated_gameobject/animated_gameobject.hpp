#pragma once
#include "gameobject/gameobject.hpp"
#include <vector>
#include <map>

template <typename anim_id>
class animated_gameobject : public GameObject {
  public:
    struct animation {
      struct keyframe {
        v3d position;
        v3d rotation;
        double time_offset;
        keyframe(const v3d &position, const v3d &rotation, double time_offset);
      };

      private:
      double total_len;

      public:
      //const double& length = total_len;
      unsigned int next_frame;
      std::vector<keyframe> frames;

      animation(std::unique_ptr<std::vector<keyframe>> frames): frames(*frames.release()) {};
      animation() {};
    };

    std::map<anim_id, animation> animations;

  private:
    v3d orig_position;
    v3d orig_rotation;
    animation *playing;
    double playing_duration;

  public:
    animated_gameobject();
    animated_gameobject(std::shared_ptr<Shape> shape);
    animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider);
    animated_gameobject(std::unique_ptr<std::map<anim_id, animation>> anims);
    animated_gameobject(std::shared_ptr<Shape> shape, std::unique_ptr<std::map<anim_id, animation>> anims);
    animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider, std::unique_ptr<std::map<anim_id, animation>> anims);

    virtual void update(double dt) override;

    bool play(anim_id to_play);
    bool recursive_play(anim_id to_play);
};

// implementations of templated stuff
#include "animated_gameobject.cpp"
