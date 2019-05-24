#include "camera.h"
#include <GL/gl.h>

Camera::Camera(void): GameObject(nullptr) {}

v3d Camera::get_forward() const {
  v3d forward = v3d::Z;

  forward.rotate(this->rotation.x, v3d::Y);
  v3d right = v3d::cross(forward, v3d::Y);
  forward.rotate(this->rotation.y, right);

  return forward;
}

v3d Camera::get_forward_xz() const {
  v3d forward = v3d::Z;

  forward.rotate(this->rotation.x, v3d::Y);
  return forward;
}

void Camera::move_to() const {
  this->pushTransform();
}
