#include <GL/gl.h>

typedef struct Colour {
  float r;
  float g;
  float b;
  float a;

  Colour(float r, float g, float b, float a);
  operator float*() { return &r; }
} Colour;

typedef struct Material {
  float shininess;
  Colour ambient;
  Colour diffuse;
  Colour specular;

  Material(float shininess, Colour ambient, Colour diffuse, Colour specular);
} Material;

GLAPI void GLAPIENTRY glMaterialfv(GLenum face, Material&);
