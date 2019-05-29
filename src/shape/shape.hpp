#pragma once
#include "../material/material.hpp"
#include <memory>

struct DrawOptions;
class Cube;
class Sphere;
class Cylinder;
class Plane;
class Mesh;
class Function;

class Shape {
  public:
    Material material;
    bool is_material_active;

    virtual bool collidesWith(const Cube&) const = 0;
    virtual bool collidesWith(const Plane&) const = 0;
    virtual bool collidesWith(const Cylinder&) const = 0;
    virtual bool collidesWith(const Sphere&) const = 0;
    virtual void update(double dt) {};
    //virtual bool collidesWith(const Mesh&) const = 0; NYI
    virtual bool collidesWith(const Function&) const = 0;// NYI

    bool collidesWith(const Shape&) const;

    Shape(const Shape &other): material(other.material), is_material_active(other.is_material_active) {};
    Shape(const Material &material) : material(material), is_material_active(true) {};
    Shape(): is_material_active(false) {};

    virtual std::unique_ptr<Shape> clone() const = 0;

  protected:
    virtual void really_draw(const DrawOptions &options) const = 0;
  public:
    virtual void draw(const DrawOptions &options) const;
};

