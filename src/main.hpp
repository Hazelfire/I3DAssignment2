#pragma once

#include <iostream>
#include <memory>

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
#include "scene/scene.hpp"
#include "shape/primitives/primitives.hpp"
#include "shape/primitives/function/function.hpp"
#include "player/player.hpp"
#include "frog.hpp"
#include <cmath>

#define UNIT_TESTS 0

std::shared_ptr<GameObject> focus = std::make_shared<GameObject>(nullptr);
std::shared_ptr<Camera> player_camera = std::make_shared<Camera>();
std::shared_ptr<Player> player = std::make_shared<Player>();
DrawOptions drawOpts;


void handle_keys();
