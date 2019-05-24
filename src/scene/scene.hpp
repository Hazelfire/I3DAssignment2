#pragma once
#include <vector>
#include <string>
#include <memory>
#include "gameobject/gameobject.hpp"

class Scene {
  private:
  public:
    std::vector<std::pair<GameObject, std::string>> gameObjects;
    Scene();
    void add(GameObject obj, std::string tag);
    std::vector<GameObject> getObjectsByTag(std::string tag);
    void draw();
};

