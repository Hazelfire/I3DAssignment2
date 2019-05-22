#pragma once
#include <vector>
#include <string>
#include "gameobject/gameobject.h"

class Scene {
  private:
    std::vector<std::pair<GameObject, std::string>> gameObjects;
  public:
    Scene();
    void add(GameObject obj, std::string tag);
    std::vector<GameObject> getObjectsByTag(std::string tag);
    void draw();
};

