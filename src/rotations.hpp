#define _USE_MATH_DEFINES // for M_PI, M_PI_2 = pi/2 etc..
#include <cmath>


class Matrix3x3f {
	public:
	float data[9];
};

class Vec3f {
	public: 
	Vec3f(float a_x, float a_y, float a_z) : 
		x(a_x)
		, y(a_y)
		, z(a_z) 
	{}

	public:
	float x;
	float y;
	float z;
};

Vec3f ZYZ_angles_from_rotation_matrix(const Matrix3x3f& R);