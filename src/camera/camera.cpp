#include "camera.h"
#include <GL/gl.h>

camera::camera(void): rotation(v3d::zero), position(v3d::zero) {}

v3d camera::get_forward() const {
	v3d forward = v3d::Z;

	forward.rotate(this->rotation.x, v3d::Y);
	v3d right = v3d::cross(forward, v3d::Y);
	forward.rotate(this->rotation.y, right);

	return forward;
}

v3d camera::get_forward_xz() const {
	v3d forward = v3d::Z;

	forward.rotate(this->rotation.x, v3d::Y);
	return forward;
}

void camera::move_to() const {
	glRotatef(rotation.y, -1,0,0);
	glRotatef(rotation.x, 0,1,0);
	glTranslatef(position.x, position.y, position.z);
}
