#pragma once
#include "../../vector/vector.h"// keeping track of relative dirs is why i setup generated_directories.h - you only have to setup the relative dir once per file
#include "../shape.hpp"

class Cube : public Shape{
	public:
		Cube(v3d position, v3d size): position(position), size(size){};
		v3d position;
		v3d size;
		bool collidesWith(Cube);
		bool collidesWith(Plane);
		bool collidesWith(Cylinder);
		bool collidesWith(Sphere);
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
		void draw() const;
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
		void draw() const;
};
