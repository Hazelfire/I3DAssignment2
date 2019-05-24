#pragma once
#include "../material/material.hpp"

class Cube;
class Sphere;
class Cylinder;
class Plane;
class Mesh;
class Function;

class Shape {
  public:
    Material material;
    virtual bool collidesWith(Cube &c) = 0;
    virtual bool collidesWith(Plane &p) = 0;
    virtual bool collidesWith(Cylinder &c) = 0;
    virtual bool collidesWith(Sphere &s) = 0;
    //virtual bool collidesWith(Mesh) = 0; NYI
    //virtual bool collidesWith(Function) = 0; NYI

    Shape(const Shape &other): material(other.material) {};
    Shape(const Material &material) : material(material) {};
    Shape() {};

    virtual void draw() const = 0;
};

