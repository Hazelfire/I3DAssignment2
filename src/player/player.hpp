#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Player : public GameObject {
  private:
    v3d jumpV = v3d::unit;
    v3d velocity = v3d::zero;
    bool grounded = true;

    void drawJump();
  public:
    void jump();
    Player();
    virtual void draw() override;
    virtual void update(double dt) override;
};
