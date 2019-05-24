#pragma once
#include "../../vector/vector.h"// keeping track of relative dirs is why i setup generated_directories.h - you only have to setup the relative dir once per file
#include "../shape.hpp"

class Cube : public Shape{
	public:
		Cube(v3d position, v3d size);
		v3d position;
		v3d size;
		virtual bool collidesWith(Cube) const override;
		virtual bool collidesWith(Plane) const override;
		virtual bool collidesWith(Cylinder) const override;
		virtual bool collidesWith(Sphere) const override;
		void draw() const;
};

class Function : public Shape {
	public:
		// is is possible to put the implemmentation in the cpp file?
		Function(v3d position, v3d size): position(position), size(size) {};
		//Function(v3d position, v3d size);
		v3d position;
		v3d size;
		virtual double f(double x, double z) const = 0;
		virtual double df_x(double x, double z) const = 0;//dy/dx
		virtual double df_z(double x, double z) const = 0;//dy/dz
		virtual bool collidesWith(Cube) const override;//NYI
		virtual bool collidesWith(Plane) const override;//NYI
		virtual bool collidesWith(Cylinder) const override;//NYI
		virtual bool collidesWith(Sphere) const override;//NYI
#define DRAW_FUNCTION_NORMALS 0
		void draw() const;
};

class Sphere : public Shape{
	public:
		Sphere(v3d, double);
		v3d position;
		double radius;
		virtual bool collidesWith(Cube) const override;
		virtual bool collidesWith(Plane) const override;
		virtual bool collidesWith(Cylinder) const override;
		virtual bool collidesWith(Sphere) const override;
		double distance(const Sphere&) const;
		void draw() const;
};

class Plane : public Shape{
	public:
		Plane(double height): height(height){};
		double height;
		virtual bool collidesWith(Cube) const override;
		virtual bool collidesWith(Plane) const override;
		virtual bool collidesWith(Cylinder) const override;
		virtual bool collidesWith(Sphere) const override;
		void draw() const;//NYI
};

class Cylinder : public Shape{
	public:
		Cylinder(v3d position, double radius, double length);
		v3d position;
		double radius;
		double length;
		virtual bool collidesWith(Cube) const override;
		virtual bool collidesWith(Plane) const override;
		virtual bool collidesWith(Cylinder) const override;
		virtual bool collidesWith(Sphere) const override;
		void draw() const;
};
