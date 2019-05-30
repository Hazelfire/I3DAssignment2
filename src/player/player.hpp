#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Player : public GameObject {
  private:
    v3d velocity = v3d::zero;
    bool grounded = true;

    void drawJump() const;
    GameObject* boundTo;
    v3d boundDistance;
    bool bound;
  public:
    v3d jumpV = v3d::unit;
    void jump();
    void ground();
    void bind(GameObject& other);
    Player();
    virtual void draw(DrawOptions options) const override;
    virtual void update(double dt) override;
};
