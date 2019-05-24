#pragma once
#include <vector>
#include <string>
#include <memory>
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Scene {
  private:
    std::vector<std::pair<std::shared_ptr<GameObject>, std::string>> gameObjects;
  public:
    Scene();
    void add(std::shared_ptr<GameObject> obj, std::string tag);
    std::vector<std::shared_ptr<GameObject>> getObjectsByTag(std::string tag);
    void draw(DrawOptions options);
    void update(double dt);
};

