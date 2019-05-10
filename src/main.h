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

#include <cmath>

#define UNIT_TESTS 0

#include "generated_directories.h"
#include VECTOR_H
#include CAMERA_H
#include TIME_H
#include KEYBOARD_H

camera player_camera;


void handle_keys();
