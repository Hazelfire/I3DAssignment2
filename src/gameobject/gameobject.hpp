#pragma once
#include <memory>
#include "shape/shape.hpp"

using namespace std;

class GameObject {
  private:
    shared_ptr<Shape> shape;
  public:
    GameObject(Shape* shape);
    void draw();
};
