#include "primitives.hpp"
#include <cmath>
#include <GL/gl.h>

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

void Sphere::draw() const {
	//NYI
	position.draw();

	//TODO use global tesselation value to determine slices and stacks
	int stack_height = 4;
	int slices = 4;

	//                                 |
	//                    ____z_____v1 |
	//            /|     |         _/  |
	//           / |     |       _/    |
	//          /  |     |     _/      |
	//       h1/   |   h1|   _/h2      |
	//        /    |y    | _/          |
	//       /     |     |/            |
	//     v0______|    v0             |
	//          x                      |
	//                                 |
	//                                 |
	//                                 |
	//                                 |
	//                                 |
	//                                 |
	//                                 |

	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glScaled(size.x, size.y, size.z);
	for(int slice = 0; slice < slices; slice++) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0,0,radius);
		
		glEnd();
	}
	for(int stack = 0; stack < stack_height-2; stack++) {
		for(int slice = 0; slice < 2; slice++) {
			glBegin(GL_QUAD_STRIP);
			glEnd();
		}
	}
	for(int slice = 0; slice < slices; slice++) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0,0,-1*radius);
		glEnd();
	}
	glPopMatrix();
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

void Cube::draw() const {
	//                                 |
	//       2---------6               |
	//      /|        /|               |
	//     / |       / |    Y          |
	//    /  |      /  |    |          |
	//   3---------7   |    |          |
	//   |   |     |   |    |          |
	//   |   0-----|---4    *---X      |
	//   |  /      |  /    /           |
	//   | /       | /    /            |
	//   |/        |/    Z             |
	//   1---------5                   |
	//                                 |
	//                                 |
	//     0---4---6---2               |
	//     |   |   |   |               |
	//     |   |   |   |               |
	//     1---5---7---3---2---6       |
	//             |   |   |   |       |
	//             |   |   |   |       |
	//             5---1---0---4       |
	//                                 |

	v3d points[8] = {
		v3d(0,0,0),
		v3d(0,0,1),
		v3d(0,1,0),
		v3d(0,1,1),
		v3d(1,0,0),
		v3d(1,0,1),
		v3d(1,1,0),
		v3d(1,1,1),
	};
	for(int i = 0; i < 8; i++) {
		points[i] -= v3d::unit / 2;
	}

	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glScaled(size.x, size.y, size.z);
	glBegin(GL_QUAD_STRIP);
	points[0].draw();
	points[1].draw();
	points[4].draw();
	points[5].draw();
	points[6].draw();
	points[7].draw();
	points[2].draw();
	points[3].draw();
	glEnd();
	glBegin(GL_QUAD_STRIP);
	points[7].draw();
	points[5].draw();
	points[3].draw();
	points[1].draw();
	points[2].draw();
	points[0].draw();
	points[6].draw();
	points[4].draw();
	glEnd();
	glPopMatrix();
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

void Plane::draw() const {
	//NYI
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

void Cylinder::draw() const {
	position.draw();//NYI
}
