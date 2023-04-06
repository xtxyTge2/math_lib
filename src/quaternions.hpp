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
};

Quaternion operator*(const Quaternion& q, const Quaternion& p);
