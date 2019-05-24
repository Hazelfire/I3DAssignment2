#pragma once

class Cube;
class Sphere;
class Cylinder;
class Plane;
class Mesh;
class Function;

class Shape {
  public:
    virtual bool collidesWith(const Cube&) const = 0;
    virtual bool collidesWith(const Plane&) const = 0;
    virtual bool collidesWith(const Cylinder&) const = 0;
    virtual bool collidesWith(const Sphere&) const = 0;
    //virtual bool collidesWith(const Mesh&) const = 0; NYI
    //virtual bool collidesWith(const Function&) const = 0; NYI

    virtual void draw() const = 0;
};

