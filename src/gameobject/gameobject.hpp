#pragma once
#include <memory>
#include "shape/shape.hpp"
#include "vector/vector.h"
#include "shape/primitives/primitives.hpp"

//using namespace std;

struct Transform {
  v3d position;
  v3d rotation;
  v3d scale;
};

class GameObject {
  private:
    std::shared_ptr<GameObject> parent;
  public:
    std::shared_ptr<Shape> shape;
    v3d position;
    v3d rotation;

    GameObject(Shape* shape);
    GameObject(Shape* shape, std::shared_ptr<GameObject> parent);

    // deep copies the shape
    // shallow copies the parent - preserves heirarchy
    GameObject(const GameObject&);

    virtual void draw(DrawOptions ops);
    void pushTransform() const;
    void popTransform() const;
    void setParent(std::shared_ptr<GameObject> parent);
    virtual void update(double dt);
};
