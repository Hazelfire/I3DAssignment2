#pragma once
#include "../material/material.hpp"

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

    virtual bool collidesWith(const Cube&) const = 0;
    virtual bool collidesWith(const Plane&) const = 0;
    virtual bool collidesWith(const Cylinder&) const = 0;
    virtual bool collidesWith(const Sphere&) const = 0;
    virtual void update(double dt) {};
    //virtual bool collidesWith(const Mesh&) const = 0; NYI
    //virtual bool collidesWith(const Function&) const = 0; NYI

    Shape(const Shape &other): material(other.material) {};
    Shape(const Material &material) : material(material) {};
    Shape() {};

    virtual void draw(DrawOptions options) const = 0;
};

