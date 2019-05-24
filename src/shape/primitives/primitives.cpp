#include "primitives.hpp"
#include <cmath>
#include <GL/gl.h>

// Sphere
//Sphere::Sphere(Material material, v3d position, double radius): Shape(material), position(position), radius(radius) {};
//Sphere::Sphere(v3d position, double radius): Sphere(Material(), position, radius) {};

double Sphere::distance(Sphere &other){
	return 0;//other.position.distance(this->position) - this->radius - other.radius;
}

bool Sphere::collidesWith(Sphere &other){
	return false;//this->distance(other) <= 0;
}

bool Sphere::collidesWith(Cube &other){
	return false;
}

bool Sphere::collidesWith(Plane &other){
	return false;//other.height > (this->position.y - this->radius);
}

bool Sphere::collidesWith(Cylinder &other){
	return false;
}

void Sphere::draw() const {
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_NORMALIZE);
	glTranslated(position.x, position.y, position.z);
	glScaled(radius, radius, radius);

	// TODO set n from global tessalation value
	const int n = 200;
	const int slices=n, stacks=n;
	double step_phi = M_PI / stacks;


	// start of sphere...
	// simplified case, since the pole stays the same
	{
		glBegin(GL_TRIANGLE_FAN);
		double sin_phi_step = sinf(step_phi);
		double cos_phi_step = cosf(step_phi);

		v3d start(0, 0, 1);
		start.glNormal();
		start.glVertex();

		// end point is the same as the start point...
		// needs to be drawn twice
		for(int i = 0; i <= slices; i++) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d curr(sin_phi_step * cos_theta,
					sin_phi_step * sin_theta,
					cos_phi_step);
			curr.glNormal();
			curr.glVertex();
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

			v3d curr(sin_phi * cos_theta,
					sin_phi * sin_theta,
					cos_phi);
			curr.glNormal();
			curr.glVertex();

			v3d step(sin_phi_step * cos_theta,
					sin_phi_step * sin_theta,
					cos_phi_step);
			step.glNormal();
			step.glVertex();
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
		v3d start(0, 0, -1);
		start.glNormal();
		start.glVertex();

		// end point is the same as the start point...
		// needs to be drawn twice
		for (int i = slices; i >= 0; i--) {
			double theta = i / (double)slices * 2.0 * M_PI;
			double cos_theta = cosf(theta);
			double sin_theta = sinf(theta);
			v3d curr(sin_phi * cos_theta,
					sin_phi * sin_theta,
					cos_phi);
			curr.glNormal();
			curr.glVertex();
		}
		glEnd();
	}
	glPopMatrix();
	glPopAttrib();
}

// Function
//Function::Function(v3d position, v3d size): position(position), size(size) {};
bool Function::collidesWith(Cube &other){
	return false;
}

bool Function::collidesWith(Plane &other){
	return false;
}

bool Function::collidesWith(Cylinder &other){
	return false;
}

bool Function::collidesWith(Sphere &other){
	return false;
}

void Function::draw() const {
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_NORMALIZE);
	glTranslated(position.x, position.y, position.z);
	glScaled(size.x, size.y, size.z);

	//glBegin(GL_POINTS);

	// TODO set n from global tessalation value
	const int n = 80;
	double y_vals[n][n];
	v3d normals[n][n];
	v3d x_tan[n][n];
	v3d z_tan[n][n];

	for(int i = 0; i < n; i++) {
		double x = (double)i / n - 0.5;
		for(int j = 0; j < n; j++) {
			double z = (double)j / n - 0.5;
			y_vals[i][j] = f(x, z);
			double dy_x = df_x(x, z);
			double dy_z = df_z(x, z);


			v3d current(x, y_vals[i][j], z);

			/*
			 * tangent of f(x) at x=a
			 * f(x)
			 * g(x) = d/dx f(x)
			 * b = f(a)
			 *
			 * tangent equation:
			 *   y = g(a)x + (b - g(a) * a)
			 */

			double new_x = x + 1.0/n;
			v3d x_next = v3d(new_x, dy_x * new_x + (y_vals[i][j] - dy_x * x), z) - current;
			x_tan[i][j] = x_next + current;

			double new_z = z + 1.0/n;
			v3d z_next = v3d(x, dy_z * new_z + (y_vals[i][j] - dy_z * z), new_z) - current;
			z_tan[i][j] = z_next + current;

			// TODO: check if the 2 vectors are already the same length, and if they can be easily normalised
			v3d normal = v3d::cross(v3d::normalise(z_next), v3d::normalise(x_next));
			// 2nd normalise doesn't need to be done, because we have opengl normalising for us
			normals[i][j] = normal;
		}
	}


	for(int i = 0; i < n-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		double x = (double)i / n - 0.5;
		for(int j = 0; j < n; j++) {
			double z = (double)j / n - 0.5;

			normals[i+1][j].glNormal();
			v3d(x + 1.0/n, y_vals[i+1][j], z).glVertex();

			normals[i][j].glNormal();
			v3d(x, y_vals[i][j], z).glVertex();
		}
		glEnd();
	}

#if DRAW_FUNCTION_NORMALS
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	for(int i = 0; i < n; i++) {
		double x = (double)i / n - 0.5;
		for(int j = 0; j < n; j++) {
			double z = (double)j / n - 0.5;

			// draw normals
			glColor3f(0,1,0);
			v3d current(x, y_vals[i][j], z);
			current.glVertex();
			(current + normals[i][j] * 1.0/n).glVertex();

			// draw x tangents
			glColor3f(1,0,0);
			current.glVertex();
			x_tan[i][j].glVertex();

			// draw z tangents
			glColor3f(0,0,1);
			current.glVertex();
			z_tan[i][j].glVertex();
		}
	}
	glEnd();
#endif
	glPopMatrix();
	glPopAttrib();
}


// Cube
//Cube::Cube(Material material, v3d position, v3d size): Shape(material), position(position), size(size){};
//Cube::Cube(v3d position, v3d size): Cube(Material(), position, size) {};
bool Cube::collidesWith(Sphere &other){
	return false;//other.collidesWith(*this);
}

bool Cube::collidesWith(Cube &other){
	return false;
}

bool Cube::collidesWith(Plane &other){
	return false;
}

// Bad implementation, pretends the cylinder is a cube
bool Cube::collidesWith(Cylinder &other){
	return false;
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
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_NORMALIZE);
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
		points[5].glVertex();
		v3d::X.glNormal();
		points[4].glVertex();
		v3d::X.glNormal();
		points[6].glVertex();
		v3d::X.glNormal();
		points[7].glVertex();

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
		points[1].glVertex();
		(-1*v3d::Y).glNormal();
		points[0].glVertex();
		(-1*v3d::Y).glNormal();
		points[4].glVertex();
		(-1*v3d::Y).glNormal();
		points[5].glVertex();
	}
	{
		//+z
		v3d::Z.glNormal();
		points[3].glVertex();
		v3d::Z.glNormal();
		points[1].glVertex();
		v3d::Z.glNormal();
		points[5].glVertex();
		v3d::Z.glNormal();
		points[7].glVertex();
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
	glPopAttrib();
}

// Plane
bool Plane::collidesWith(Sphere &other){
	return false;//other.collidesWith(*this);
}

bool Plane::collidesWith(Cube &other){
	return false;//other.collidesWith(*this);
}

bool Plane::collidesWith(Plane &other){
	return false;//height == other.height;
}

bool Plane::collidesWith(Cylinder &other){
	return false;//other.position.y + other.radius > height && other.position.y - other.radius < height;
}

void Plane::draw() const {
	//NYI
}

// Cylinder
//Cylinder::Cylinder(Material material, v3d position, double radius, double length): Shape(material), position(position), radius(radius), length(length) {};
//Cylinder::Cylinder(v3d position, double radius, double length): Cylinder(Material(), position, radius, length) {};

bool Cylinder::collidesWith(Sphere &other){
	return false;//other.collidesWith(*this);
}

bool Cylinder::collidesWith(Cube &other){
	return false;//other.collidesWith(*this);
}

bool Cylinder::collidesWith(Plane &other){
	return false;//other.collidesWith(*this);
}

bool Cylinder::collidesWith(Cylinder &other){
	return false;
}

void Cylinder::draw() const {
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_NORMALIZE);
	glTranslated(position.x, position.y, position.z);
	glScaled(radius, radius, length);

	// TODO set n from global tessalation value
	const int n = 200;
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

			glNormal3f(0,0,1);
			v3d(cos_theta, sin_theta, 0.5).glVertex();
		}
		glEnd();
	}

#if CYLINDER_COLOUR
	glColor3f(1, 1,1);
#endif

#define CYLINDER_USE_STACKS 0
#if CYLINDER_USE_STACKS
	// middle of cylinder
	for(int i = 0; i <= slices; i++) {
		double theta = i / (double)slices * 2.0 * M_PI;
		double cos_theta = cosf(theta);
		double sin_theta = sinf(theta);

		v3d normal(cos_theta, sin_theta, 0);
		glBegin(GL_QUAD_STRIP);

		for(int j = 0; j < stacks; j++) {
			double zpos = (double)j / stacks - 0.5;
			double step = 1.0 / stacks;

			glNormal3f(cos_theta, sin_theta, 0);
			glVertex3f(cos_theta, sin_theta, zpos+step);

			glNormal3f(cos_theta, sin_theta, 0);
			glVertex3f(cos_theta, sin_theta, zpos);
		}
		glEnd();
	}
#else
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i <= slices; i++) {
		double theta = i / (double)slices * 2.0 * M_PI;
		double cos_theta = cosf(theta);
		double sin_theta = sinf(theta);

		glNormal3f(cos_theta, sin_theta, 0);
		v3d(cos_theta, sin_theta, 0.5).glVertex();
		glNormal3f(cos_theta, sin_theta, 0);
		v3d(cos_theta, sin_theta, -0.5).glVertex();
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

			glNormal3f(0,0,-1);
			v3d(cos_theta, sin_theta, -0.5).glVertex();
		}
		glEnd();
	}
	glPopMatrix();
	glPopAttrib();
}
