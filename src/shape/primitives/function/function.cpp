#include "function.hpp"
#include <cmath>

double Simple_Sin::f(double x, double z) const {
	return sinf(x);
}

double Simple_Sin::df_x(double x, double z) const {
	// dy/dx
	return cosf(x);
}

double Simple_Sin::df_z(double x, double z) const {
	// dy/dz
	// change with y when z changes: 0
	return 0;
}
