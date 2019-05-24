#include "material.hpp"

Colour::Colour(void): r(1), g(1), b(1), a(1) {};
Colour::Colour(float r, float g, float b, float a): r(r), g(g), b(b), a(a) {};


Material::Material(void):
  shininess(16), ambient(), diffuse(), specular() {};
Material::Material(float shininess, Colour ambient, Colour diffuse, Colour specular):
  shininess(shininess), ambient(ambient), diffuse(diffuse), specular(specular) {};
Material::Material(float shininess, Colour ambient, Colour diffuse, Colour specular, GLuint texture):
  shininess(shininess), ambient(ambient), diffuse(diffuse), specular(specular), texture(texture) {};


GLAPI void GLAPIENTRY glMaterialfv(GLenum face, const Material& material) {
  if(material.texture){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, material.texture);
  }
  glMaterialfv(face, GL_SHININESS, &material.shininess);
  glMaterialfv(face, GL_AMBIENT, material.ambient);
  glMaterialfv(face, GL_DIFFUSE, material.diffuse);
  glMaterialfv(face, GL_SPECULAR, material.specular);
}
