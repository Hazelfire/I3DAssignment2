#pragma once
#include <memory>
#include "shape/shape.hpp"
#include "vector/vector.h"
#include "shape/primitives/primitives.hpp"

using namespace std;

class Scene;

struct Transform {
  v3d position;
  v3d rotation;
  v3d scale;
};

class GameObject {
  private:
    shared_ptr<GameObject> parent;
  public:
    const Scene *scene;
    shared_ptr<Shape> shape;
    v3d position;
    v3d rotation;
    GameObject(Shape* shape);
    GameObject(const Scene*, Shape* shape);
    GameObject(const Scene*, Shape* shape, std::shared_ptr<GameObject> parent);
    bool collidesWith(const GameObject &other) const;
    virtual void draw(DrawOptions ops);
    void pushTransform() const;
    void popTransform() const;
    void setParent(std::shared_ptr<GameObject> parent);
    virtual void update(double dt);
};
