#include "function.hpp"
#include <cmath>

double Simple_Sin::f(double x, double z) const {
	return sinf(5*x);
}

double Simple_Sin::df_x(double x, double z) const {
	// dy/dx
	return cosf(5*x)*5;
}

double Simple_Sin::df_z(double x, double z) const {
	// dy/dz
	// change with y when z changes: 0
	return 0;
}


double Sin_and_Cos::f(double x, double z) const {
	return sinf(5*x) + cosf(3*z);
}

double Sin_and_Cos::df_x(double x, double z) const {
	// dy/dx
	return cosf(5*x)*5;
}

double Sin_and_Cos::df_z(double x, double z) const {
	// dy/dz
	return -1 * sinf(3*z)*3;
}
