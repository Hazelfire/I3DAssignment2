#pragma once
#include "vector/vector.h"
#include "shape/shape.hpp"

struct DrawOptions {
  bool wireframe = false;
  int tesselations = 16;
  bool drawAxes = true;
  bool normals = false;
  bool lighting = true;
  bool textures = false;
  bool animation = true;
  bool osd = false;
};

class Cube : public Shape{
  public:
    v3d position;
    v3d size;

    Cube(const Material &material, v3d position, v3d size): Shape(material), position(position), size(size) {};
    Cube(v3d position, v3d size): Shape(), position(position), size(size) {};
    Cube(const Cube &other) : Shape(other), position(other.position), size(other.size) {};
    Cube() : Shape() {}

    virtual std::unique_ptr<Shape> clone() const override;

    virtual bool collidesWith(const Cube&) const override;
    virtual bool collidesWith(const Grid&) const override;
    virtual bool collidesWith(const Cylinder&) const override;
    virtual bool collidesWith(const Sphere&) const override;
    virtual bool collidesWith(const Function&) const override;

    virtual void really_draw(const DrawOptions &options) const;
};

class Function : public Shape {
  public:
    v3d position;
    v3d size;

    // is is possible to put the implemmentation in the cpp file?
    Function(const Material &material, v3d position, v3d size): Shape(material), position(position), size(size) {};
    Function(v3d position, v3d size): Shape(), position(position), size(size) {};
    Function(const Function &other) : Shape(other), position(other.position), size(other.size) {};
    Function() : Shape() {}
    //Function(v3d position, v3d size);

    virtual double f(double x, double z) const = 0;
    virtual double df_x(double x, double z) const = 0;//dy/dx
    virtual double df_z(double x, double z) const = 0;//dy/dz

    virtual bool collidesWith(const Cube&) const override;//NYI
    virtual bool collidesWith(const Grid&) const override;//NYI
    virtual bool collidesWith(const Cylinder&) const override;//NYI
    virtual bool collidesWith(const Sphere&) const override;//NYI
    virtual bool collidesWith(const Function&) const override;//NYI

    virtual std::unique_ptr<Shape> clone() const override = 0;

#define DRAW_FUNCTION_NORMALS 0
    virtual void really_draw(const DrawOptions &options) const;
};

class Sphere : public Shape{
  public:
    v3d position;
    double radius;

    Sphere(const Material &material, v3d position, double radius): Shape(material), position(position), radius(radius) {};
    Sphere(v3d position, double radius): Shape(), position(position), radius(radius) {};
    Sphere(const Sphere &other) : Shape(other), position(other.position), radius(other.radius) {};
    Sphere() : Shape() {}

    virtual bool collidesWith(const Cube&) const override;
    virtual bool collidesWith(const Grid&) const override;
    virtual bool collidesWith(const Cylinder&) const override;
    virtual bool collidesWith(const Sphere&) const override;
    virtual bool collidesWith(const Function&) const override;

    double distance(const Sphere&) const;
    virtual void really_draw(const DrawOptions &draw) const;

    virtual std::unique_ptr<Shape> clone() const override;
};

class Grid : public Shape{
  public:
    v3d position;
    v3d size;
    double tesselation;

    Grid(const Material &material, v3d position, v3d size, int tesselation): Shape(material), position(position), size(size), tesselation(tesselation) {};
    Grid(v3d position, v3d size, int tesselation): Shape(), position(position), size(size), tesselation(tesselation) {};
    Grid(const Grid &other) : Shape(other.material), position(other.position), size(other.size), tesselation(other.tesselation) {};
    Grid() : Shape() {}

    virtual bool collidesWith(const Cube&) const override;
    virtual bool collidesWith(const Grid&) const override;
    virtual bool collidesWith(const Cylinder&) const override;
    virtual bool collidesWith(const Sphere&) const override;
    virtual bool collidesWith(const Function&) const override;

    virtual void really_draw(const DrawOptions &draw) const;//NYI

    virtual std::unique_ptr<Shape> clone() const override;
};

class Cylinder : public Shape{
  public:
    v3d position;
    double radius;
    double length;

    Cylinder(const Material &material, v3d position, double radius, double length): Shape(material), position(position), radius(radius), length(length) {};
    Cylinder(v3d position, double radius, double length): Shape(), position(position), radius(radius), length(length) {};
    Cylinder(const Cylinder &other) : Shape(other), radius(other.radius), length(other.length) {};
    Cylinder() : Shape() {}


    virtual bool collidesWith(const Cube&) const override;
    virtual bool collidesWith(const Grid&) const override;
    virtual bool collidesWith(const Cylinder&) const override;
    virtual bool collidesWith(const Sphere&) const override;
    virtual bool collidesWith(const Function&) const override;
    virtual void really_draw(const DrawOptions &draw) const;

    virtual std::unique_ptr<Shape> clone() const override;
};
