#include "camera.h"
#include <GL/gl.h>

camera::camera(void): rotation(v3d::zero), position(v3d::zero) {}


v3d camera::get_forward() const {
	v3d forward = v3d::Z;

	forward.rotate(this->rotation.x, v3d::Y);
	//this->right = -1*v3d::cross(v3d(0,1,0), forward);
	v3d right = -1*v3d::cross(v3d::Y, forward);
	forward.rotate(this->rotation.y, right);

	return forward;
}

void camera::move_to() const {
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 0,1,0);
	glRotatef(rotation.y, 0,0,1);
}
