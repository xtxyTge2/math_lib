#include <cassert>

#include "quaternions.hpp"


Quaternion operator*(const Quaternion& q, const Quaternion& p)
{
	float r = q.r * p.r - q.i * p.i - q.j * p.j - q.k * p.k;
	float i = q.r * p.i + q.i * p.r + q.j * p.k - q.k * p.j;
	float j = q.r * p.j - q.i * p.k + q.j * p.r + q.k * p.i;
	float k = q.r * p.k + q.i * p.j - q.j * p.i + q.k * p.r;

	return Quaternion(r, i, j, k);
}

Quaternion operator+(const Quaternion& q, const Quaternion& p)
{
	return Quaternion(q.r + p.r, q.i + p.i, q.j + p.j, q.k + p.k);
}

Vec3f rotate_point_around_rotation_axis_and_angle(const Vec3f v, const Vec3f& axis, float theta) 
{
	Quaternion rotation_quat = get_quaternion_from_rotation_axis_and_angle(axis, theta);

	Vec3f rotated_point = rotate_point_by_unit_quaternion(v, rotation_quat);

	return rotated_point;
}

Quaternion get_quaternion_from_rotation_axis_and_angle(const Vec3f& v, float theta) 
{
	assert(v.norm() == 1.0f); // @Robustness: it should be a floating point check not an equality check.

	float c = cos(theta / 2.0f);
	float s = sin(theta / 2.0f);

	return Quaternion(c, s*v.x, s*v.y, s*v.z);
}

Vec3f rotate_point_by_unit_quaternion(const Vec3f& v, const Quaternion p)
{
	// p has to be unit_quaternion
	assert(p.norm() == 1.0f); // @Robustness: it should be a floating point check not an equality check.
	
	Quaternion q_v = Quaternion(v); // embed vector into quaternion, as the i, j and k components.

	Quaternion res = p * q_v * p.conjugate(); 
	return res.Im(); 
}