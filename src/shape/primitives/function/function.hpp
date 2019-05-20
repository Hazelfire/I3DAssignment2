#pragma once
#include "../primitives.hpp"

class Simple_Sin : public Function {
	public:
		Simple_Sin(v3d position, v3d size): Function(position, size) {};
		double f(double x, double z) const override;
		double df_x(double x, double z) const override;
		double df_z(double x, double z) const override;
};

class Sin_and_Cos : public Function {
	public:
		Sin_and_Cos(v3d position, v3d size): Function(position, size) {};
		double f(double x, double z) const override;
		double df_x(double x, double z) const override;
		double df_z(double x, double z) const override;
};
