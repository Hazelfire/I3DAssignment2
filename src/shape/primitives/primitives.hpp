#pragma once
#include "../../vector/vector.h"// keeping track of relative dirs is why i setup generated_directories.h - you only have to setup the relative dir once per file
#include "../shape.hpp"

class Cube : public Shape{
	public:
		Cube(v3d position, v3d size);
		v3d position;
		v3d size;
		bool collidesWith(Cube);
		bool collidesWith(Plane);
		bool collidesWith(Cylinder);
		bool collidesWith(Sphere);
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
		bool collidesWith(Cube);//NYI
		bool collidesWith(Plane);//NYI
		bool collidesWith(Cylinder);//NYI
		bool collidesWith(Sphere);//NYI
		void draw() const;
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
		void draw() const;
};

class Plane : public Shape{
	public:
		Plane(double height): height(height){};
		double height;
		bool collidesWith(Cube);
		bool collidesWith(Plane);
		bool collidesWith(Cylinder);
		bool collidesWith(Sphere);
		void draw() const;//NYI
};

class Cylinder : public Shape{
	public:
		Cylinder(v3d position, double radius, double length);
		v3d position;
		double radius;
		double length;
		bool collidesWith(Cube);
		bool collidesWith(Plane);
		bool collidesWith(Cylinder);
		bool collidesWith(Sphere);
		void draw() const;
};
