#define _USE_MATH_DEFINES // for M_PI, M_PI_2 = pi/2 etc..
#include <cmath>
#include <string>
#include <format>

class Vec3f {
public: 
	Vec3f(float a_x, float a_y, float a_z) : 
		x(a_x)
		, y(a_y)
		, z(a_z) 
	{}

	float norm() const
	{
		return sqrt(x*x + y*y + z*z);
	}
public:
	float x;
	float y;
	float z;
};


class Matrix3x3f {
	public:

	Matrix3x3f() = default;

	Matrix3x3f(float a00, float a01, float a02, 
	           float a10, float a11, float a12, 
	           float a20, float a21, float a22) 
	{
		data[0] = a00;
		data[1] = a01;
		data[2] = a02;

		data[3] = a10;
		data[4] = a11;
		data[5] = a12;

		data[6] = a20;
		data[7] = a21;
		data[8] = a22;
	}

	Matrix3x3f(const Vec3f& u, const Vec3f& v, const Vec3f& w) 
	{
		data[0] = u.x;
		data[1] = u.y;
		data[2] = u.z;

		data[3] = v.x;
		data[4] = v.y;
		data[5] = v.z;

		data[6] = w.x;
		data[7] = w.y;
		data[8] = w.z;
	}

	float& operator ()(int r, int c) 
	{
		return data[3 * r + c];
	}

	const float& operator ()(int r, int c) const 
	{		
		return data[3 * r + c];
	}

	std::string to_string() const {
		return std::format("|{:.12f} {:.12f} {:.12f}|\n|{:.12f} {:.12f} {:.12f}|\n|{:.12f} {:.12f} {:.12f}|\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
	}

	private:

	float data[9];
	// row major layout, ie the entries are given in this order
	// 	| 0 1 2 |
	//  | 3 4 5 |
	//  | 6 7 8 |
};


Matrix3x3f operator*(const Matrix3x3f& M, const Matrix3x3f& N);
Vec3f operator*(const Matrix3x3f M, const Vec3f& v);

Vec3f ZXZ_angles_from_rotation_matrix(const Matrix3x3f& R);
Vec3f RPY_angles_from_rotation_matrix(const Matrix3x3f& R);

Matrix3x3f get_rotation_matrix_around_X_axis(float angle);
Matrix3x3f get_rotation_matrix_around_Y_axis(float angle);
Matrix3x3f get_rotation_matrix_around_Z_axis(float angle);