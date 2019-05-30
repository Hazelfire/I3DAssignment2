#pragma once
#include "gameobject/gameobject.hpp"
#include <vector>

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
      const double& length = total_len;
      anim_id name;
      std::vector<keyframe> frames;

      bool operator<(const animation& r) const;// for use in std::set
    };

    std::set<animation> animations;

  private:
    v3d orig_position;
    v3d orig_rotation;
    animation *playing;

  public:
    animated_gameobject();
    animated_gameobject(std::shared_ptr<Shape> shape);
    animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider);
    animated_gameobject(std::unique_ptr<std::set<animation>> &&anims);
    animated_gameobject(std::shared_ptr<Shape> shape, std::unique_ptr<std::set<animation>> &&anims);
    animated_gameobject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider, std::unique_ptr<std::set<animation>> &&anims);

    virtual void draw(DrawOptions ops) const override;


};
