#include "material.hpp"

Colour::Colour(void): r(0), g(0), b(0), a(0) {};
Colour::Colour(float r, float g, float b, float a): r(r), g(g), b(b), a(a) {};


Material::Material(void):
  shininess(0), ambient(), diffuse(), specular() {};
Material::Material(float shininess, Colour ambient, Colour diffuse, Colour specular):
  shininess(shininess), ambient(ambient), diffuse(diffuse), specular(specular) {};


GLAPI void GLAPIENTRY glMaterialfv(GLenum face, Material& material) {
  glMaterialfv(face, GL_SHININESS, &material.shininess);
  glMaterialfv(face, GL_AMBIENT, material.ambient);
  glMaterialfv(face, GL_DIFFUSE, material.diffuse);
  glMaterialfv(face, GL_SPECULAR, material.specular);
}
