#pragma once
#include <vector>
#include <string>
#include <memory>
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

namespace tag {
  enum object_tag {
    floor,
    death,
    log,
    object,
    player,
  };
}

class Scene {
  private:
    std::vector<std::pair<std::shared_ptr<GameObject>, tag::object_tag>> gameObjects;
  public:
    Scene();
    void add(std::shared_ptr<GameObject> obj, tag::object_tag tag);
    std::vector<std::shared_ptr<GameObject>> getObjectsByTag(tag::object_tag tag) const;
    std::vector<std::shared_ptr<GameObject>> getCollidingObjectsByTag(const GameObject &other, tag::object_tag tag) const;
    void draw(DrawOptions options);
    void update(double dt);
};

