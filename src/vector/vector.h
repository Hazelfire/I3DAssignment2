#pragma once

class v3d {
	public:
		static const v3d zero;
		static const v3d unit;

		double x;
		double y;
		double z;

		v3d(void);
		v3d(double x, double y, double z);

		// static methods here do not modify the inputs
		// non-static versions modify the class its called on

		double dot(const v3d&);
		static double dot(const v3d&, const v3d&);

		v3d& cross(const v3d&);
		static v3d cross(v3d, const v3d&);

		double length_squared();
		static double length_squared(const v3d&);

		double length();
		static double length(const v3d&);

		v3d& normalise();
		static v3d normalise(v3d);

		v3d &project(const v3d&);
		static v3d project(v3d, const v3d&);

		v3d &reject(const v3d&);
		static v3d reject(v3d, const v3d&);



		v3d operator+(const v3d&) const;
		v3d operator-(const v3d&) const;

		v3d& operator+=(const v3d&);
		v3d& operator-=(const v3d&);

		v3d operator*(double) const;
		v3d operator/(double) const;

		v3d& operator*=(double);
		v3d& operator/=(double);
};

// make the (*, /) operators symmetric
v3d operator*(double, const v3d&);
v3d operator/(double, const v3d&);
