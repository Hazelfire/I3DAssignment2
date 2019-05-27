#pragma once
#include <memory>
#include <vector>
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
    std::weak_ptr<GameObject> parent;
    std::vector<std::shared_ptr<GameObject>> children;
  public:
    std::shared_ptr<Shape> shape;
    std::weak_ptr<GameObject> self;
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
    void setParent(std::shared_ptr<GameObject>);
    virtual void update(double dt);
};
