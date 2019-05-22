#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Player : public GameObject {
  public:
    Player();
    void draw(DrawOptions opts);
};
