#pragma once

#include <memory>

class _time {
	_time(void);
	static std::unique_ptr<_time> instance;

	public:
	double start;
	double current;
	double last;
	double delta;

	static const _time& get_instance();
	static void update(int elapsed_milliseconds);
};
