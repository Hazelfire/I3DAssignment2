#pragma once
#include "../vector/vector.h"

class Cube;
class Sphere;
class Cylinder;
class Plane;

class Shape {
  public:
    virtual bool collidesWith(Cube) = 0;
    virtual bool collidesWith(Plane) = 0;
    virtual bool collidesWith(Cylinder) = 0;
    virtual bool collidesWith(Sphere) = 0;
};

class Cube : public Shape{
  public:
    Cube(v3d position, v3d size): position(position), size(size){};
    v3d position;
    v3d size;
    bool collidesWith(Cube);
    bool collidesWith(Plane);
    bool collidesWith(Cylinder);
    bool collidesWith(Sphere);
};

class Sphere : public Shape{
  public:
    Sphere(v3d, double);
    v3d position;
    double radius;
    bool collidesWith(Cube);
    bool collidesWith(Plane);
    bool collidesWith(Cylinder);
    bool collidesWith(Sphere);
    double distance(Sphere);
};

class Plane : public Shape{
  public:
    Plane(double height): height(height){};
    double height;
    bool collidesWith(Cube);
    bool collidesWith(Plane);
    bool collidesWith(Cylinder);
    bool collidesWith(Sphere);
};

class Cylinder : public Shape{
  public:
    Cylinder(v3d position, double radius, double length): position(position), radius(radius), length(length) {};
    v3d position;
    double radius;
    double length;
    bool collidesWith(Cube);
    bool collidesWith(Plane);
    bool collidesWith(Cylinder);
    bool collidesWith(Sphere);
};
