#include "shape.hpp"


void Shape::draw(const DrawOptions &options) const {
  // push settings
  glPushAttrib(GL_NORMALIZE);
  glPushAttrib(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  if(is_material_active)
    glMaterialfv(GL_FRONT_AND_BACK, material);

  really_draw(options);

  glPopAttrib();
  glPopAttrib();
}
