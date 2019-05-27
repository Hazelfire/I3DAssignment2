#pragma once
#include "../primitives.hpp"

class Simple_Sin : public Function {
  public:
    Simple_Sin(Material material, v3d position, v3d size): Function(material, position, size) {};
    Simple_Sin(v3d position, v3d size): Function(position, size) {};

    virtual double f(double x, double z) const override;
    virtual double df_x(double x, double z) const override;
    virtual double df_z(double x, double z) const override;

    virtual std::unique_ptr<Shape> clone() const override;
};

class Sin_and_Cos : public Function {
  public:
    Sin_and_Cos(Material material, v3d position, v3d size): Function(material, position, size) {};
    Sin_and_Cos(v3d position, v3d size): Function(position, size) {};

    virtual double f(double x, double z) const override;
    virtual double df_x(double x, double z) const override;
    virtual double df_z(double x, double z) const override;

    virtual std::unique_ptr<Shape> clone() const override;
};

class Tute_Water : public Function {
  public:
    double x_mul;
    double z_mul;
    double t_mul;
    double t;

    Tute_Water(Material material, v3d position, v3d size): Function(material, position, size), 
      x_mul(1), z_mul(1), t_mul(1), t(0) {};
    Tute_Water(v3d position, v3d size): Function(position, size), 
      x_mul(1), z_mul(1), t_mul(1), t(0) {};
    virtual void update(double dt) {t += dt;}
    virtual double f(double x, double z) const override;
    virtual double df_x(double x, double z) const override;
    virtual double df_z(double x, double z) const override;

    virtual std::unique_ptr<Shape> clone() const override;
};
