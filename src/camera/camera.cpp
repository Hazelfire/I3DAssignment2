#include "camera.h"
#include <GL/gl.h>

Camera::Camera(void): GameObject(nullptr) {}

v3d Camera::get_forward() const {
  Transform tf = this->getWorldTransform();
  v3d forward = v3d::Z;

  forward.rotate(tf.rotation.x, v3d::Y);
  v3d right = v3d::cross(forward, v3d::Y);
  forward.rotate(tf.rotation.y, right);

  return forward;
}

v3d Camera::get_forward_xz() const {
  Transform tf = this->getWorldTransform();
  v3d forward = v3d::Z;

  forward.rotate(tf.rotation.x, v3d::Y);
  return forward;
}

void Camera::move_to() const {
  Transform tf = this->getWorldTransform();
  glRotatef(tf.rotation.y, 0,1,0);
  glRotatef(tf.rotation.x, 1,0,0);
  glTranslatef(tf.position.x, tf.position.y, tf.position.z);
}
