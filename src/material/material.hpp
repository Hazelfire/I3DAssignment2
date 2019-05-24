#include <GL/gl.h>

struct Colour {
  float r;
  float g;
  float b;
  float a;

  Colour(void);
  Colour(float r, float g, float b, float a);
  //Colour(const Colour &c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
  operator float*() { return &r; }
};

struct Material {
  float shininess;
  Colour ambient;
  Colour diffuse;
  Colour specular;

  Material(void);
  Material(float shininess, Colour ambient, Colour diffuse, Colour specular);
  //Material(const Material &m) : shininess(m.shininess), ambient(m.ambient), diffuse(m.diffuse), specular(m.specular) {}
};

GLAPI void GLAPIENTRY glMaterialfv(GLenum face, Material&);
