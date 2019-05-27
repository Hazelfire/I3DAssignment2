#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Player : public GameObject {
  private:
    v3d velocity = v3d::zero;
    bool grounded = true;

    void drawJump();
  public:
    v3d jumpV = v3d::unit;
    void jump();
    void ground();
    Player();
    virtual void draw(DrawOptions options) override;
    virtual void update(double dt) override;
};
