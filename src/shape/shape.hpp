#pragma once

class Cube;
class Sphere;
class Cylinder;
class Plane;
class Mesh;
class Function;

class Shape {
  public:
    virtual bool collidesWith(Cube) = 0;
    virtual bool collidesWith(Plane) = 0;
    virtual bool collidesWith(Cylinder) = 0;
    virtual bool collidesWith(Sphere) = 0;
    //virtual bool collidesWith(Mesh) = 0; NYI
    //virtual bool collidesWith(Function) = 0; NYI

    virtual void draw() const = 0;
};

