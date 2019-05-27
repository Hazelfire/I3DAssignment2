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
    static std::unique_ptr<Scene> instance;
    std::vector<std::pair<std::shared_ptr<GameObject>, tag::object_tag>> gameObjects;
    Scene();

  public:
    static const Scene& get_instance();
    ~Scene();

    // side-effect methods
    static void add(std::shared_ptr<GameObject> obj, tag::object_tag tag);
    static void update(double dt);

    // const methods - use get_instance
    std::vector<std::shared_ptr<GameObject>> getObjectsByTag(tag::object_tag tag) const;
    std::vector<std::shared_ptr<GameObject>> getCollidingObjectsByTag(const GameObject &other, tag::object_tag tag) const;
    void draw(DrawOptions options) const;
};

