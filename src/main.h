#pragma once

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define USE_FREEGLUT 0
#if USE_FREEGLUT
#include <GL/freeglut.h>
#else
void glutBitmapString(void *font, char *str);
#endif

#include "generated_directories.h"
#include VECTOR_H
