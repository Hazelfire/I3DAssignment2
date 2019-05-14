#include "primitives.hpp"
#include <cmath>

// Sphere
Sphere::Sphere(v3d position, double radius): position(position), radius(radius) {};

double Sphere::distance(Sphere other){
	return other.position.distance(this->position) - this->radius - other.radius;
}

bool Sphere::collidesWith(Sphere other){
	return this->distance(other) <= 0;
}

bool Sphere::collidesWith(Cube other){
	bool insideX = this->position.x + this->radius > other.position.x - (other.size.x / 2) && this->position.x - this->radius < other.position.x + (other.size.x / 2);
	bool insideY = this->position.y + this->radius > other.position.y - (other.size.y / 2) && this->position.y - this->radius < other.position.y + (other.size.y / 2);
	bool insideZ = this->position.z + this->radius > other.position.z - (other.size.z / 2) && this->position.z - this->radius < other.position.z + (other.size.z / 2);
	return insideX && insideY && insideZ;
}

bool Sphere::collidesWith(Plane other){
	return other.height > (this->position.y - this->radius);
}

bool Sphere::collidesWith(Cylinder other){
	double diffz = position.z - other.position.z;
	double diffy = position.y - other.position.y;
	bool insideLength = sqrt(diffy * diffy + diffz * diffz) < radius + other.radius;
	bool insideX = position.x + radius > other.position.x - (other.length / 2) && position.x - radius < other.position.x + (other.length / 2);
	
	return insideX && insideLength;
}


// Cube
bool Cube::collidesWith(Sphere other){
	return other.collidesWith(*this);
}

bool Cube::collidesWith(Cube other){
	bool insideX = this->position.x + (this->size.x / 2) > other.position.x - (other.size.x / 2) && this->position.x - ( this->size.x / 2 ) < other.position.x + (other.size.x / 2);
	bool insideY = this->position.y + (this->size.y / 2) > other.position.y - (other.size.y / 2) && this->position.y - ( this->size.y / 2 ) < other.position.y + (other.size.y / 2);
	bool insideZ = this->position.z + (this->size.z / 2) > other.position.z - (other.size.z / 2) && this->position.z - ( this->size.z / 2 ) < other.position.z + (other.size.z / 2);
	return insideX && insideY && insideZ;
}

bool Cube::collidesWith(Plane other){
	return other.height > (this->position.y - this->size.y / 2);
}

// Bad implementation, pretends the cylinder is a cube
bool Cube::collidesWith(Cylinder other){
	bool insideX = position.x + (size.x / 2) > other.position.x - other.radius && position.x - ( size.x / 2 ) < other.position.x + other.radius;
	bool insideY = position.y + (size.y / 2) > other.position.y - other.radius && position.y - ( size.y / 2 ) < other.position.y + other.radius;
	bool insideZ = position.z + (size.z / 2) > other.position.z - other.radius && position.z - ( size.z / 2 ) < other.position.z + other.radius;
	return insideX && insideY && insideZ;
}


// Plane
bool Plane::collidesWith(Sphere other){
	return other.collidesWith(*this);
}

bool Plane::collidesWith(Cube other){
	return other.collidesWith(*this);
}

bool Plane::collidesWith(Plane other){
	return height == other.height;
}

bool Plane::collidesWith(Cylinder other){
	return other.position.y + other.radius > height && other.position.y - other.radius < height;
}

// Cylinder


bool Cylinder::collidesWith(Sphere other){
	return other.collidesWith(*this);
}

bool Cylinder::collidesWith(Cube other){
	return other.collidesWith(*this);
}

bool Cylinder::collidesWith(Plane other){
	return other.collidesWith(*this);
}

bool Cylinder::collidesWith(Cylinder other){
	double diffz = position.z - other.position.z;
	double diffy = position.y - other.position.y;
	bool insideLength = sqrt(diffy * diffy + diffz * diffz) < radius + other.radius;
	bool insideX = position.x + length / 2 > other.position.x - (other.length / 2) && position.x - length / 2 < other.position.x + (other.length / 2);
	return insideX && insideLength;
}
