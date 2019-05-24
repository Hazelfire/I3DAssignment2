#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Player : public GameObject {
  private:
    v3d jump = v3d::unit;

    void drawJump();
  public:
    Player();
    virtual void draw() override;
};
