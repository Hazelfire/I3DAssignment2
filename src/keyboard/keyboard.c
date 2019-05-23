#include "keyboard.h"

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
  *held &= kb_ctrl ^ 0xFFFFF;
}

void c_release(char key, enum keys *held) {
  switch(key) {
    case '\027':
    case 'w':
      *held &= kb_w ^ 0xFFFFF;
      break;
    case '\023':
    case 's':
      *held &= kb_s ^ 0xFFFFF;
      break;
    case '\001':
    case 'a':
      *held &= kb_a ^ 0xFFFFF;
      break;
    case '\004':
    case 'd':
      *held &= kb_d ^ 0xFFFFF;
      break;
    case '\000':
    case ' ':
      *held &= kb_space ^ 0xFFFFF;
      break;
    case '\003':
    case 'c':
      *held &= kb_c ^ 0xFFFFF;
      break;
  }
}
