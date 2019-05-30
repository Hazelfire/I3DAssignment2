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

      anim_id name;
      std::vector<keyframe> frames;

      bool operator<(const animation& r) const;// for use in std::set
    };

    std::set<animation> animations;

  private:
    v3d orig_position;
    v3d orig_rotation;

  public:
    virtual void draw(DrawOptions ops) override;
};
