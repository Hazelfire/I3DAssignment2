#pragma once
#include "shape/shape.hpp"


class GameObject {
  private:
    Shape& shape;
  public:
    GameObject(Shape&);
    void draw();
};
