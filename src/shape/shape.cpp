#include "shape.hpp"

// this is required because we want to dynamic cast to the different shapes for arbitrary collision
#include "shape/primitives/primitives.hpp"


void Shape::draw(const DrawOptions &options) const {
  // push settings
  glPushAttrib(GL_ENABLE_BIT);
  glPushAttrib(GL_NORMALIZE);
  glPushAttrib(GL_COLOR_MATERIAL);

  glEnable(GL_NORMALIZE);
  if(is_material_active)
    glMaterialfv(GL_FRONT_AND_BACK, material);

  really_draw(options);

  glPopAttrib();
  glPopAttrib();
  glPopAttrib();
}

bool Shape::collidesWith(const Shape& other) const {
  const Cube *cube = dynamic_cast<const Cube *>(&other);
  if(cube) {
    return collidesWith(*cube);
  }
  const Sphere *sphere = dynamic_cast<const Sphere *>(&other);
  if(sphere) {
    return collidesWith(*sphere);
  }
  const Cylinder *cylinder = dynamic_cast<const Cylinder *>(&other);
  if(cylinder) {
    return collidesWith(*cylinder);
  }
  const Grid *plane = dynamic_cast<const Grid *>(&other);
  if(plane) {
    return collidesWith(*plane);
  }
  //const Mesh *mesh = dynamic_cast<const Mesh *>(&other);
  //if(mesh) {
  //	return collidesWith(*mesh);
  //}
  const Function *function = dynamic_cast<const Function *>(&other);
  if(function) {
    return collidesWith(*function);
  }

  return false;
}
