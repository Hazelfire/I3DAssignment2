#include "camera.h"
#include <GL/gl.h>

camera::camera(void): rotation(v3d::zero), position(v3d::zero) {}


void camera::move_to() const {
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 0,1,0);
	glRotatef(rotation.y, 0,0,1);
}
