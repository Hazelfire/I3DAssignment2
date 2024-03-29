#pragma once

#include <memory>

extern "C" {
#include "keyboard.h"
}

class keyboard {
  keyboard(void);
  static std::unique_ptr<keyboard> instance;

  public:
  enum keys held;

  static const keyboard& get_instance();

  static void hold(char key);
  static void release(char key);

  static void hold_ctrl();
  static void release_ctrl();

  static void hold_special(int key);
  static void release_special(int key);
};
