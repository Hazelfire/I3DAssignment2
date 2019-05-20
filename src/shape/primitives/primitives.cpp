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
	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glScaled(radius, radius, radius);

	// TODO set n from global tessalation value
	const int n = 8;
	const int slices=n, stacks=n;
	double step_phi = M_PI / stacks;


	// start of sphere...
	// simplified case, since the pole stays the same
	{
		glBegin(GL_TRIANGLE_FAN);
		double sin_phi_step = sinf(step_phi);
		double cos_phi_step = cosf(step_phi);

		v3d(0, 0, 1).draw();

		// end point is the same as the start point...
		// needs to be drawn twice
		for(int i = 0; i <= slices; i++) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d(sin_phi_step * cos_theta,
					sin_phi_step * sin_theta,
					cos_phi_step).draw();
		}
		glEnd();
	}


#if 1
	// middle of sphere
	for (int j = 1; j < stacks-1; j++) {
		double phi = j / (double)stacks * M_PI;
		glBegin(GL_QUAD_STRIP);
		double sin_phi = sinf(phi);
		double sin_phi_step = sinf(phi+step_phi);
		double cos_phi = cosf(phi);
		double cos_phi_step = cosf(phi+step_phi);

		for (int i = 0; i <= slices; i++) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d(sin_phi * cos_theta,
					sin_phi * sin_theta,
					cos_phi).draw();
			v3d(sin_phi_step * cos_theta,
					sin_phi_step * sin_theta,
					cos_phi_step).draw();
		}
		glEnd();
	}
#endif


	// end of sphere...
	// simplified case, since the pole stays the same
	{
		double phi = (stacks-1) / (double)stacks * M_PI;
		glBegin(GL_TRIANGLE_FAN);
		double sin_phi = sinf(phi);
		double cos_phi = cosf(phi);
		v3d(0, 0, -1).draw();

		// end point is the same as the start point...
		// needs to be drawn twice
		for (int i = slices; i >= 0; i--) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d(sin_phi * cos_theta,
					sin_phi * sin_theta,
					cos_phi).draw();
		}
		glEnd();
	}
	glPopMatrix();
}

// Function
//Function::Function(v3d position, v3d size): position(position), size(size) {};

void Function::draw() const {
	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glScaled(size.x, size.y, size.z);

	// TODO set n from global tessalation value
	const int n = 8;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
		}
	}
	glPopMatrix();
}


// Cube
Cube::Cube(v3d position, v3d size): position(position), size(size){};
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
#define CUBE_USE_STRIPS 0
	// can't use strips for cube lighting, since the 
#if CUBE_USE_STRIPS
	glBegin(GL_QUAD_STRIP);
	points[1].draw();
	points[0].draw();
	points[5].draw();
	points[4].draw();
	points[7].draw();
	points[6].draw();
	points[3].draw();
	points[2].draw();
	glEnd();
	glBegin(GL_QUAD_STRIP);
	points[5].draw();
	points[7].draw();
	points[1].draw();
	points[3].draw();
	points[0].draw();
	points[2].draw();
	points[4].draw();
	points[6].draw();
	glEnd();
#else
	glBegin(GL_QUADS);
	{
		//+x
		v3d::X.glNormal();
		points[4].glVertex();
		v3d::X.glNormal();
		points[5].glVertex();
		v3d::X.glNormal();
		points[7].glVertex();
		v3d::X.glNormal();
		points[6].glVertex();
		
		//-x
		(-1*v3d::X).glNormal();
		points[0].glVertex();
		(-1*v3d::X).glNormal();
		points[1].glVertex();
		(-1*v3d::X).glNormal();
		points[3].glVertex();
		(-1*v3d::X).glNormal();
		points[2].glVertex();
	}
	{
		//+y
		v3d::Y.glNormal();
		points[2].glVertex();
		v3d::Y.glNormal();
		points[3].glVertex();
		v3d::Y.glNormal();
		points[7].glVertex();
		v3d::Y.glNormal();
		points[6].glVertex();
		//-y
		(-1*v3d::Y).glNormal();
		points[0].glVertex();
		(-1*v3d::Y).glNormal();
		points[1].glVertex();
		(-1*v3d::Y).glNormal();
		points[5].glVertex();
		(-1*v3d::Y).glNormal();
		points[4].glVertex();
	}
	{
		//+z
		v3d::Z.glNormal();
		points[1].glVertex();
		v3d::Z.glNormal();
		points[3].glVertex();
		v3d::Z.glNormal();
		points[7].glVertex();
		v3d::Z.glNormal();
		points[5].glVertex();
		//-z
		(-1*v3d::Z).glNormal();
		points[0].glVertex();
		(-1*v3d::Z).glNormal();
		points[2].glVertex();
		(-1*v3d::Z).glNormal();
		points[6].glVertex();
		(-1*v3d::Z).glNormal();
		points[4].glVertex();
	}
	glEnd();
#endif
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
Cylinder::Cylinder(v3d position, double radius, double length): position(position), radius(radius), length(length) {};

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
	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glScaled(radius, radius, length);

	// TODO set n from global tessalation value
	const int n = 8;
	const int slices=n, stacks=n;

	// for some reason, there is an artifact on the inside of the cylinder
	// in the non-stack mode.
	// not quite sure why. since turning on CYLINDER_COLOUR makes the
	// artifact go away
#define CYLINDER_COLOUR 0
#if CYLINDER_COLOUR
	glColor3f(0,1,1);
#endif

	// start of cylinder...
	// simplified case, since the pole stays the same
	{
		glBegin(GL_POLYGON);

		for(int i = 0; i < slices; i++) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d(cos_theta, sin_theta, 0.5).draw();
		}
		glEnd();
	}

#if CYLINDER_COLOUR
	glColor3f(1, 1,1);
#endif

#define CYLINDER_USE_STACKS 0
#if CYLINDER_USE_STACKS
	// middle of cylinder
	for(int j = 0; j < stacks; j++) {
		double zpos = (double)j / stacks - 0.5;
		double step = 1.0 / stacks;
		glBegin(GL_QUAD_STRIP);

		for(int i = 0; i <= slices; i++) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d(cos_theta, sin_theta, zpos+step).draw();
			v3d(cos_theta, sin_theta, zpos).draw();
		}
		glEnd();
	}
#else
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i <= slices; i++) {
		double theta = i / (double)slices * 2.0 * M_PI;
		double cos_theta = cosf(theta);
		double sin_theta = sinf(theta);
		v3d(cos_theta, sin_theta, 0.5).draw();
		v3d(cos_theta, sin_theta, -0.5).draw();
	}
	glEnd();
#endif

#if CYLINDER_COLOUR
	glColor3f(1, 0.1,0.1);
#endif

	// end of cylinder...
	// simplified case, since the pole stays the same
	if(1) {
		glBegin(GL_POLYGON);

		// reverse order, so that the end is facing outwards
		for (int i = slices; i > 0; i--) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d(cos_theta, sin_theta, -0.5).draw();
		}
		glEnd();
	}
	glPopMatrix();
}
