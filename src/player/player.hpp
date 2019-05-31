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
    double time_till_ribbet = 0;
  public:
    bool dead = false;
    int lives = 5;
    int score = 0;
    unsigned int time_between_ribbet = 10;

    v3d jumpV = v3d(0, 1.5, 1);
    void jump();
    void ribbet(double dt);
    void ground();
    void bind(GameObject& other);
    void reset();
    Player();
    virtual void draw(DrawOptions options) const override;
    virtual void update(double dt) override;
};
