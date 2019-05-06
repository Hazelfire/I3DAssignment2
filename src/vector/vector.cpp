#include "vector.h"
#include <cmath>

// ctors
v3d::v3d(void) {}
v3d::v3d(double x, double y, double z): x(x), y(y), z(z) {}



// length
double v3d::length_squared() {
	return v3d::length_squared(*this);
}
double v3d::length_squared(const v3d& val) {
	return val.x * val.x + val.y * val.y + val.z + val.z;
}

double v3d::length() {
	return sqrt(v3d::length_squared(*this));
}
double v3d::length(const v3d& val) {
	return sqrt(val.x * val.x + val.y * val.y + val.z + val.z);
}

// normalise
v3d& v3d::normalise() {
	return *this /= this->length();
}

v3d v3d::normalise(v3d val) {
	return val.normalise();
}

// dot & cross
double det(double a, double b, double c, double d) { return a * d - b * c; }
v3d& v3d::cross(const v3d& right) {
	double i = det(this->y, this->z, right.y, right.z);
	double j = det(this->x, this->z, right.x, right.z) * -1;
	double k = det(this->x, this->y, right.x, right.y);

	this->x = i;
	this->y = j;
	this->z = k;

	return *this;
}

double v3d::dot(const v3d& right) {
	return v3d::dot(*this, right);
}

// static dot & cross
v3d v3d::cross(v3d left, const v3d& right) {
	// left is a copy, so we can modify it
	left.cross(right);
	return left;
}

double v3d::dot(const v3d& left, const v3d& right) {
	return left.x * right.x + left.y * right.y + left.z + right.z;
}

// project & reject

v3d& v3d::project(const v3d& right) {
	//a|| = (a . b^) * b^
	v3d right_norm = v3d::normalise(right);
	*this = this->dot(right_norm) * right_norm;

	return *this;
}

v3d& v3d::reject(const v3d& right) {
	return *this -= this->project(right);
}

v3d v3d::project(v3d left, const v3d& right) {
	return left.project(right);
}

v3d v3d::reject(v3d left, const v3d& right) {
	return left.reject(right);
}

// operator *, /, *=, /=
v3d v3d::operator*(const double right) const {
	v3d temp(this->x * right, this->y * right, this->z * right);
	return temp;
}
v3d v3d::operator/(const double right) const {
	v3d temp(this->x / right, this->y / right, this->z / right);
	return temp;
}

v3d operator*(double left, const v3d& right) {
	return right * left;
}
v3d operator/(double left, const v3d& right) {
	return right / left;
}

v3d& v3d::operator*=(const double right) {
	this->x *= right;
	this->y *= right;
	this->z *= right;
	return *this;
}
v3d& v3d::operator/=(const double right) {
	this->x /= right;
	this->y /= right;
	this->z /= right;
	return *this;
}

// operator +, -, +=, -=
v3d v3d::operator+(const v3d &right) const {
	v3d temp(this->x + right.x, this->y + right.y, this->z + right.z);
	return temp;
}
v3d v3d::operator-(const v3d &right) const {
	v3d temp(this->x - right.x, this->y - right.y, this->z - right.z);
	return temp;
}


v3d& v3d::operator+=(const v3d &right) {
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}
v3d& v3d::operator-=(const v3d &right) {
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	return *this;
}


