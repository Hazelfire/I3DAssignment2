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

#include "vector/vector.h"
#include "camera/camera.h"
#include "time/time.h"
#include "keyboard/keyboard.hpp"
#include "keyboard/keyboard.h"
#include "shape/primitives/primitives.hpp"
#define UNIT_TESTS 0

camera player_camera;


void handle_keys();
