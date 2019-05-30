#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"

class Car : public GameObject {
  private:
    double t = 0.0;
    double carSpeed = 2;
  public:
    Car(v3d position, double speed);
    virtual void update(double dt) override;
    virtual void draw(DrawOptions options) const override;
};
