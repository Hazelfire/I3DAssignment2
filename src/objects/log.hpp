#pragma once
#include "gameobject/gameobject.hpp"
#include "shape/primitives/primitives.hpp"
#include <GL/gl.h>

class Log : public GameObject {
  private:
    double t = 0.0;
    double logSpeed;
  public:
    Log(v3d position, GLuint texture, double speed);
    virtual void update(double dt) override;
    virtual void draw(DrawOptions opts) const override;
};
