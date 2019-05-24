#ifndef KEYBOARD_C_H
#define KEYBOARD_C_H

/*
 * it was either this, or define a bunch
 * of bitwise operator overloads
 */

enum keys {
  kb_w = 1 << 0,
  kb_s = 1 << 1,
  kb_a = 1 << 2,
  kb_d = 1 << 3,
  kb_space = 1 << 4,
  kb_c = 1 << 5,
  kb_right = 1 << 6,
  kb_left = 1 << 7,
  kb_up = 1 << 8,
  kb_down = 1 << 9,
  kb_ctrl = 1 << 10,
};

void c_hold(char key, enum keys*);
void c_release(char key, enum keys*);

void c_hold_ctrl(enum keys*);
void c_release_ctrl(enum keys*);

void c_special_hold(int key, enum keys*);
void c_special_release(int key, enum keys*);


#endif
