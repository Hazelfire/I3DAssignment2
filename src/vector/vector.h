#pragma once
#include <iostream>

#ifndef PI
// nasa approved 15 digits of PI
#define PI 3.141592653589793
#endif

class v3d {
  public:
    static const v3d zero;
    static const v3d unit;
    static const v3d X;
    static const v3d Y;
    static const v3d Z;

    double x;
    double y;
    double z;

    v3d(void);
    v3d(double x, double y, double z);

    void draw() const;// draw line from 0 to vector
    void draw(const v3d &pos) const;// draw line from pos to vector
    void draw(double x, double y, double z) const;// draw line from x,y,z to vector+x,y,z

    void glVertex() const;//deprecated
    void glNormal() const;//deprecated
    friend void glVertex3f(const v3d&);
    friend void glVertex3d(const v3d&);
    friend void glNormal3f(const v3d&);
    friend void glNormal3d(const v3d&);
    friend void glRotatef(float angle, const v3d& axis);
    friend void glRotated(float angle, const v3d& axis);
    friend void glTranslatef(const v3d&);
    friend void glTranslated(const v3d&);

    // static methods here do not modify the inputs
    // non-static versions modify the class its called on

    double dot(const v3d&) const;
    static double dot(const v3d&, const v3d&);

    v3d& cross(const v3d&);
    static v3d cross(v3d, const v3d&);

    double distance(const v3d&) const;
    static double distance(const v3d&, const v3d&);

    double length_squared() const;
    static double length_squared(const v3d&);

    double length() const;
    static double length(const v3d&);

    v3d& normalise();
    static v3d normalise(v3d);
    
    v3d &project(const v3d&);
    static v3d project(v3d, const v3d&);

    v3d &reject(const v3d&);
    static v3d reject(v3d, const v3d&);

    v3d &rotate(double angle, const v3d &axis);
    static v3d rotate(v3d to_rotate, double angle, const v3d &axis);

    bool is_valid() const;
    static bool is_valid(const v3d&);


    v3d operator+(const v3d&) const;
    v3d operator-(const v3d&) const;

    v3d& operator+=(const v3d&);
    v3d& operator-=(const v3d&);

    v3d operator*(double) const;
    v3d operator/(double) const;
    friend v3d operator*(double, const v3d&);
    friend v3d operator/(double, const v3d&);

    v3d& operator*=(double);
    v3d& operator/=(double);

    friend std::ostream& operator<<(std::ostream&, const v3d&);
};


namespace test {
  bool rotate();
}
