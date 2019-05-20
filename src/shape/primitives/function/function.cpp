#include "function.hpp"
#include <cmath>

double Simple_Sin::f(double x, double z) {
	return sinf(x) + z;
}

double Simple_Sin::df(double x, double z) {
	return cosf(x);
}
