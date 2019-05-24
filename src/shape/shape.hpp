#pragma once

class Cube;
class Sphere;
class Cylinder;
class Plane;
class Mesh;
class Function;

class Shape {
  public:
    virtual bool collidesWith(Cube) const = 0;
    virtual bool collidesWith(Plane) const = 0;
    virtual bool collidesWith(Cylinder) const = 0;
    virtual bool collidesWith(Sphere) const = 0;
    //virtual bool collidesWith(Mesh) const = 0; NYI
    //virtual bool collidesWith(Function) const = 0; NYI

    virtual void draw() const = 0;
};

