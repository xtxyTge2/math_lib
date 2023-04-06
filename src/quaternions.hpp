#include "rotations.hpp"

class Quaternion {
public:
	float r;
	float i;
	float j;
	float k;

	Quaternion() = default;

	Quaternion(float a_r) :
		r(a_r)
		, i(0.0f)
		, j(0.0f)
		, k(0.0f)
	{};

	Quaternion(const Vec3f& v) :
		r(0.0f)
		, i(v.x)
		, j(v.y)
		, k(v.z)
	{};

	Quaternion(float a_r, float a_i, float a_j, float a_k) :
		r(a_r)
		, i(a_i)
		, j(a_j)
		, k(a_k)
	{};

	Quaternion conjugate() const
	{
		return Quaternion(r, -i, -j, -k);
	};

	float norm() const
	{
		return sqrt(r*r + i*i + j*j + k*k);
	}

	float Re() const
	{
		return r;
	}

	Vec3f Im() const
	{
		return Vec3f(i, j, k);
	}
};

Quaternion operator*(const Quaternion& q, const Quaternion& p);
Quaternion operator+(const Quaternion& q, const Quaternion& p);


Vec3f rotate_point_around_rotation_axis_and_angle(const Vec3f v, const Vec3f& axis, float theta);
Quaternion get_quaternion_from_rotation_axis_and_angle(const Vec3f& v, float theta);
Vec3f rotate_point_by_unit_quaternion(const Vec3f& v, const Quaternion p);