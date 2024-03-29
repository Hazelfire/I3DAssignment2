#include "keyboard.hpp"

std::unique_ptr<keyboard> keyboard::instance = nullptr;

keyboard::keyboard(void) {
  held = (keys)0x00;
}

const keyboard& keyboard::get_instance() {
  if(instance == nullptr) {
    instance = std::make_unique<keyboard>(keyboard());
  }

  return *instance.get();
}

void keyboard::hold(char key) {
  c_hold(key, &instance->held);
}

void keyboard::release(char key) {
  c_release(key, &instance->held);
}

void keyboard::hold_ctrl() {
  c_hold_ctrl(&instance->held);
}
void keyboard::release_ctrl() {
  c_release_ctrl(&instance->held);
}

void keyboard::hold_special(int key){
  c_special_hold(key, &instance->held);
}

void keyboard::release_special(int key){
  c_special_release(key, &instance->held);
}
