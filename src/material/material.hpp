#pragma once
#include <GL/gl.h>

struct Colour {
  // volatile stops compiler from optimising out my vars...
  // so we get array-like behavior, with the nice variable access
  float r;
  volatile float g;
  volatile float b;
  volatile float a;

  Colour(void);
  Colour(float r, float g, float b, float a);
  //Colour(const Colour &c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
  operator float*() { return &r; }
  operator const float*() const { return &r; }
};

struct Material {
  float shininess;
  Colour ambient;
  Colour diffuse;
  Colour specular;
  GLuint texture = 0;

  Material(void);
  Material(float shininess, Colour ambient, Colour diffuse, Colour specular);
  Material(float shininess, Colour ambient, Colour diffuse, Colour specular, GLuint texture);
  //Material(const Material &m) : shininess(m.shininess), ambient(m.ambient), diffuse(m.diffuse), specular(m.specular) {}
};

GLAPI void GLAPIENTRY glMaterialfv(GLenum face, const Material&);
