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
    bool dead = false;
    int lives = 5;
    int score = 0;

    v3d jumpV = v3d(0, 1, 1);
    void jump();
    void ground();
    void bind(GameObject& other);
    void reset();
    Player();
    virtual void draw(DrawOptions options) const override;
    virtual void update(double dt) override;
};
