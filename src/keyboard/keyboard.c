#include "keyboard.h"
#include <GL/freeglut.h>

void c_hold(char key, enum keys *held) {
  switch(key) {
    case '\027':
    case 'w':
      *held |= kb_w;
      break;
    case '\023':
    case 's':
      *held |= kb_s;
      break;
    case '\001':
    case 'a':
      *held |= kb_a;
      break;
    case '\004':
    case 'd':
      *held |= kb_d;
      break;
    case '\000':
    case ' ':
      *held |= kb_space;
      break;
    case '\003':
    case 'c':
      *held |= kb_c;
      break;
  }
}

void c_hold_ctrl(enum keys *held) {
  *held |= kb_ctrl;
}

void c_release_ctrl(enum keys *held) {
  *held &= kb_ctrl ^ UINT_MAX;
}

void c_release(char key, enum keys *held) {
  switch(key) {
    case '\027':
    case 'w':
      *held &= kb_w ^ UINT_MAX;
      break;
    case '\023':
    case 's':
      *held &= kb_s ^ UINT_MAX;
      break;
    case '\001':
    case 'a':
      *held &= kb_a ^ UINT_MAX;
      break;
    case '\004':
    case 'd':
      *held &= kb_d ^ UINT_MAX;
      break;
    case '\000':
    case ' ':
      *held &= kb_space ^ UINT_MAX;
      break;
    case '\003':
    case 'c':
      *held &= kb_c ^ UINT_MAX;
      break;
  }
}

void c_special_hold(int key, enum keys *held){
  switch(key){
    case GLUT_KEY_UP:
      *held |= kb_up;
      break;
    case GLUT_KEY_DOWN:
      *held |= kb_down;
      break;
    case GLUT_KEY_RIGHT:
      *held |= kb_right;
      break;
    case GLUT_KEY_LEFT:
      *held |= kb_left;
      break;
  } 
}

void c_special_release(int key, enum keys *held){
  switch(key){
    case GLUT_KEY_UP:
      *held &= kb_up ^ UINT_MAX;
      break;
    case GLUT_KEY_DOWN:
      *held &= kb_down ^ UINT_MAX;
      break;
    case GLUT_KEY_RIGHT:
      *held &= kb_right ^ UINT_MAX;
      break;
    case GLUT_KEY_LEFT:
      *held &= kb_left ^ UINT_MAX;
      break;
  } 
}
