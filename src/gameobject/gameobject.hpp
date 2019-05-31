#pragma once
#include <memory>
#include <set>
#include "shape/shape.hpp"
#include "vector/vector.h"
#include "shape/primitives/primitives.hpp"

class Scene;

struct Transform {
  v3d position;
  v3d rotation;
  v3d scale;
};

#define GO_DEBUG_LABELS 0
class GameObject : public std::enable_shared_from_this<GameObject> {
  protected:
  public:
    std::weak_ptr<GameObject> parent;
    std::set<std::shared_ptr<GameObject>> children;

    GameObject(const GameObject&);
  public:
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Shape> collider;
    v3d position;
    v3d rotation;

    GameObject();
    GameObject(std::shared_ptr<Shape> shape);
    GameObject(std::shared_ptr<Shape> shape, std::shared_ptr<Shape> collider);

    virtual void operator=(const GameObject&);

#if GO_DEBUG_LABELS
    std::string name;
#endif

    // deep copies the shape
    // shallow copies the parent - preserves heirarchy
    virtual std::shared_ptr<GameObject> clone() const;
    virtual std::shared_ptr<GameObject> clone(std::shared_ptr<GameObject> new_parent) const;
    void setParent(std::shared_ptr<GameObject>);

    bool collidesWith(const GameObject &other) const;
    virtual void draw(DrawOptions ops) const;

    void pushTransform() const;
    void popTransform() const;
    void pushRelativeTransform() const;
    void popRelativeTransform() const;

    virtual void update(double dt);
    void recursive_update(double dt);


#ifdef TEST_ACCESS
  public:
    std::shared_ptr<GameObject> get_parent() {return parent.lock();};
    std::set<std::shared_ptr<GameObject>> get_children() {return children;};
#endif
};
