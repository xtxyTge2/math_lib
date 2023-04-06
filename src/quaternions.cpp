#include "quaternions.hpp"


Quaternion operator*(const Quaternion& q, const Quaternion& p)
{
	float r = q.r * p.r - q.i * p.i - q.j * p.j - q.k * p.k;
	float i = q.r * p.i + q.i * p.r + q.j * p.k - q.k * p.j;
	float j = q.r * p.j - q.i * p.k + q.j * p.r + q.k * p.i;
	float k = q.r * p.k + q.i * p.j - q.j * p.i + q.k * p.r;

	return Quaternion(r, i, j, k);
}