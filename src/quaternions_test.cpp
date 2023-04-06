#include <cmath>
#include "quaternions.hpp"

#include "gtest/gtest.h"
namespace {

	TEST(quaternions_test, rijk_multiplication_table) 
	{
		// Tests the basic multiplication table for quaternions, ie stuff like i*i = j * j = k * k = -1 and ij = k etc.
	
		Quaternion r(186.0f, 0.0f, 0.0f, 0.0f);
		Quaternion i(0.0f, 1.0f, 0.0f, 0.0f);
		Quaternion j(0.0f, 0.0f, 1.0f, 0.0f);
		Quaternion k(0.0f, 0.0f, 0.0f, 1.0f);
		
		Quaternion rr = r*r;
		EXPECT_FLOAT_EQ(rr.r, r.r * r.r);
		EXPECT_FLOAT_EQ(rr.i, 0.0f);
		EXPECT_FLOAT_EQ(rr.j, 0.0f);
		EXPECT_FLOAT_EQ(rr.k, 0.0f);

		Quaternion ii = i*i;
		EXPECT_FLOAT_EQ(ii.r, -1.0f);
		EXPECT_FLOAT_EQ(ii.i, 0.0f);
		EXPECT_FLOAT_EQ(ii.j, 0.0f);
		EXPECT_FLOAT_EQ(ii.k, 0.0f);

		Quaternion jj = j*j;
		EXPECT_FLOAT_EQ(jj.r, -1.0f);
		EXPECT_FLOAT_EQ(jj.i, 0.0f);
		EXPECT_FLOAT_EQ(jj.j, 0.0f);
		EXPECT_FLOAT_EQ(jj.k, 0.0f);

		Quaternion kk = k*k;
		EXPECT_FLOAT_EQ(kk.r, -1.0f);
		EXPECT_FLOAT_EQ(kk.i, 0.0f);
		EXPECT_FLOAT_EQ(kk.j, 0.0f);
		EXPECT_FLOAT_EQ(kk.k, 0.0f);

		Quaternion ri = r*i; // expected: ri
		EXPECT_FLOAT_EQ(ri.r, 0.0f);
		EXPECT_FLOAT_EQ(ri.i, r.r * 1.0f);
		EXPECT_FLOAT_EQ(ri.j, 0.0f);
		EXPECT_FLOAT_EQ(ri.k, 0.0f);

		Quaternion rj = r*j; // expected: rj
		EXPECT_FLOAT_EQ(rj.r, 0.0f);
		EXPECT_FLOAT_EQ(rj.i, 0.0f);
		EXPECT_FLOAT_EQ(rj.j, r.r * 1.0f);
		EXPECT_FLOAT_EQ(rj.k, 0.0f);

		Quaternion rk = r*k; // expected: rk
		EXPECT_FLOAT_EQ(rk.r, 0.0f);
		EXPECT_FLOAT_EQ(rk.i, 0.0f);
		EXPECT_FLOAT_EQ(rk.j, 0.0f);
		EXPECT_FLOAT_EQ(rk.k, r.r * 1.0f);
	
		Quaternion ir = i*r; // expected: ri
		EXPECT_FLOAT_EQ(ir.r, 0.0f);
		EXPECT_FLOAT_EQ(ir.i, 1.0f * r.r);
		EXPECT_FLOAT_EQ(ir.j, 0.0f);
		EXPECT_FLOAT_EQ(ir.k, 0.0f);

		Quaternion ij = i*j; // expected: k
		EXPECT_FLOAT_EQ(ij.r, 0.0f);
		EXPECT_FLOAT_EQ(ij.i, 0.0f);
		EXPECT_FLOAT_EQ(ij.j, 0.0f);
		EXPECT_FLOAT_EQ(ij.k, 1.0f);

		Quaternion ik = i*k; // expected: -j
		EXPECT_FLOAT_EQ(ik.r, 0.0f);
		EXPECT_FLOAT_EQ(ik.i, 0.0f);
		EXPECT_FLOAT_EQ(ik.j, -1.0f);
		EXPECT_FLOAT_EQ(ik.k, 0.0f);
		
		Quaternion jr = j*r; // expected: jr
		EXPECT_FLOAT_EQ(jr.r, 0.0f);
		EXPECT_FLOAT_EQ(jr.i, 0.0f);
		EXPECT_FLOAT_EQ(jr.j, 1.0f * r.r);
		EXPECT_FLOAT_EQ(jr.k, 0.0f);

		Quaternion ji = j*i; // expected: -k
		EXPECT_FLOAT_EQ(ji.r, 0.0f);
		EXPECT_FLOAT_EQ(ji.i, 0.0f);
		EXPECT_FLOAT_EQ(ji.j, 0.0f);
		EXPECT_FLOAT_EQ(ji.k, -1.0f);

		Quaternion jk = j*k; // expected: i
		EXPECT_FLOAT_EQ(jk.r, 0.0f);
		EXPECT_FLOAT_EQ(jk.i, 1.0f);
		EXPECT_FLOAT_EQ(jk.j, 0.0f);
		EXPECT_FLOAT_EQ(jk.k, 0.0f);

		Quaternion kr = k*r; // expected: jk
		EXPECT_FLOAT_EQ(kr.r, 0.0f);
		EXPECT_FLOAT_EQ(kr.i, 0.0f);
		EXPECT_FLOAT_EQ(kr.j, 0.0f);
		EXPECT_FLOAT_EQ(kr.k, 1.0f * r.r);

		Quaternion ki = k*i; // expected: j
		EXPECT_FLOAT_EQ(ki.r, 0.0f);
		EXPECT_FLOAT_EQ(ki.i, 0.0f);
		EXPECT_FLOAT_EQ(ki.j, 1.0f);
		EXPECT_FLOAT_EQ(ki.k, 0.0f);

		Quaternion kj = k*j; // expected: -i
		EXPECT_FLOAT_EQ(kj.r, 0.0f);
		EXPECT_FLOAT_EQ(kj.i, -1.0f);
		EXPECT_FLOAT_EQ(kj.j, 0.0f);
		EXPECT_FLOAT_EQ(kj.k, 0.0f);
	}
} // namespace