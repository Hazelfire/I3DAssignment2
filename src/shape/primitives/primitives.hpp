#pragma once
#include "vector/vector.h"// keeping track of relative dirs is why i setup generated_directories.h - you only have to setup the relative dir once per file
#include "shape/shape.hpp"

struct DrawOptions {
  bool wireframe = false;
  int tesselations = 16;
};

class Cube : public Shape{
	public:
		v3d position;
		v3d size;

		Cube(const Material &material, v3d position, v3d size): Shape(material), position(position), size(size){};
		Cube(v3d position, v3d size): Cube(Material(), position, size) {};
		Cube(const Cube &other) : Shape(other.material), position(other.position), size(other.size) {};
		Cube() : Shape() {}

		virtual bool collidesWith(const Cube&) const override;
		virtual bool collidesWith(const Plane&) const override;
		virtual bool collidesWith(const Cylinder&) const override;
		virtual bool collidesWith(const Sphere&) const override;
		virtual void draw() const;
};

class Function : public Shape {
	public:
		v3d position;
		v3d size;

		// is is possible to put the implemmentation in the cpp file?
		Function(const Material &material, v3d position, v3d size): Shape(material), position(position), size(size) {};
		Function(v3d position, v3d size): Function(Material(), position, size) {};
		Function(const Function &other) : Shape(other.material), position(other.position), size(other.size) {};
		Function() : Shape() {}
		//Function(v3d position, v3d size);

		virtual double f(double x, double z) const = 0;
		virtual double df_x(double x, double z) const = 0;//dy/dx
		virtual double df_z(double x, double z) const = 0;//dy/dz

		virtual bool collidesWith(const Cube&) const override;//NYI
		virtual bool collidesWith(const Plane&) const override;//NYI
		virtual bool collidesWith(const Cylinder&) const override;//NYI
		virtual bool collidesWith(const Sphere&) const override;//NYI

#define DRAW_FUNCTION_NORMALS 0
		virtual void draw() const;
};

class Sphere : public Shape{
	public:
		v3d position;
		double radius;

		Sphere(const Material &material, v3d position, double radius): Shape(material), position(position), radius(radius) {};
		Sphere(v3d position, double radius): Sphere(Material(), position, radius) {};
		Sphere(const Sphere &other) : Shape(other.material), position(other.position), radius(other.radius) {};
		Sphere() : Shape() {}

		virtual bool collidesWith(const Cube&) const override;
		virtual bool collidesWith(const Plane&) const override;
		virtual bool collidesWith(const Cylinder&) const override;
		virtual bool collidesWith(const Sphere&) const override;
		double distance(const Sphere&) const;
		virtual void draw() const;
};

class Plane : public Shape{
	public:
		double height;

		Plane(const Material &material, double height): Shape(material), height(height){};
		Plane(double height): Plane(Material(), height) {};
		Plane(const Plane &other) : Shape(other.material), height(other.height) {};
		Plane() : Shape() {}

		virtual bool collidesWith(const Cube&) const override;
		virtual bool collidesWith(const Plane&) const override;
		virtual bool collidesWith(const Cylinder&) const override;
		virtual bool collidesWith(const Sphere&) const override;
		virtual void draw() const;//NYI
};

class Cylinder : public Shape{
	public:
		v3d position;
		double radius;
		double length;

		Cylinder(const Material &material, v3d position, double radius, double length): Shape(material), position(position), radius(radius), length(length) {};
		Cylinder(v3d position, double radius, double length): Cylinder(Material(), position, radius, length) {};
		Cylinder(const Cylinder &other) : Shape(other.material), radius(other.radius), length(other.length) {};
		Cylinder() : Shape() {}

		virtual bool collidesWith(const Cube&) const override;
		virtual bool collidesWith(const Plane&) const override;
		virtual bool collidesWith(const Cylinder&) const override;
		virtual bool collidesWith(const Sphere&) const override;
		virtual void draw() const;
};
