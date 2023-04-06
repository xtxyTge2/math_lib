#define _USE_MATH_DEFINES // for M_PI, M_PI_2 = pi/2 etc..
#include <cmath>


class Matrix3x3f {
	public:
	float data[9];

	// row major layout, ie the entries are given in this order
	// 	| 0 1 2 |
	//  | 3 4 5 |
	//  | 6 7 8 |
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

Vec3f ZXZ_angles_from_rotation_matrix(const Matrix3x3f& R);
Vec3f RPY_angles_from_rotation_matrix(const Matrix3x3f& R);

Matrix3x3f get_rotation_matrix_around_X_axis(float angle);
Matrix3x3f get_rotation_matrix_around_Y_axis(float angle);
Matrix3x3f get_rotation_matrix_around_Z_axis(float angle);