#pragma once
#include <memory>
#include "shape/shape.hpp"
#include "vector/vector.h"

using namespace std;

struct Transform {
  v3d position;
  v3d rotation;
  v3d scale;
};

class GameObject {
  private:
    shared_ptr<GameObject> parent;
    shared_ptr<Shape> shape;
  public:
    v3d position;
    v3d rotation;
    GameObject(Shape* shape);
    GameObject(Shape* shape, std::shared_ptr<GameObject> parent);
    void draw();
    Transform getWorldTransform() const;
    void setParent(std::shared_ptr<GameObject> parent);
};
