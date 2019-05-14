#include "time.h"

std::unique_ptr<_time> _time::instance = nullptr;

_time::_time(void) {
  start = 0;
  current = 0;
  last = 0;
}


const _time& _time::get_instance() {
  if(instance == nullptr) {
    instance = std::make_unique<_time>(_time());
  }

  return *instance.get();
}

void _time::update(int elapsed_milliseconds) {
  // update last time
  instance->last = instance->current;

  // calculate current time
  instance->current = elapsed_milliseconds / (double)1000 - instance->start;

  instance->delta = instance->current - instance->last;
}
