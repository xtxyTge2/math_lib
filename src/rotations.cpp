#include "rotations.hpp"



Matrix3x3f operator *(const Matrix3x3f& M, const Matrix3x3f& N)
{
	return Matrix3x3f(M(0,0) * N(0,0) + M(0,1) * N(1, 0) + M(0, 2) * N(2, 0), 
	                  M(0,0) * N(0,1) + M(0,1) * N(1, 1) + M(0, 2) * N(2, 1),
	                  M(0,0) * N(0,2) + M(0,1) * N(1, 2) + M(0, 2) * N(2, 2),

	                  M(1,0) * N(0,0) + M(1,1) * N(1, 0) + M(1, 2) * N(2, 0),
	                  M(1,0) * N(0,1) + M(1,1) * N(1, 1) + M(1, 2) * N(2, 1),
	                  M(1,0) * N(0,2) + M(1,1) * N(1, 2) + M(1, 2) * N(2, 2),
	                  
	                  M(2,0) * N(0,0) + M(2,1) * N(1, 0) + M(2, 2) * N(2, 0),
	                  M(2,0) * N(0,1) + M(2,1) * N(1, 1) + M(2, 2) * N(2, 1),
	                  M(2, 0) * N(0, 2) + M(2, 1) * N(1, 2) + M(2, 2) * N(2, 2));
};

Vec3f operator *(const Matrix3x3f M, const Vec3f& v) 
{
	return Vec3f(M(0,0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
	             M(1,0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
	             M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z);
}

/*
	Computes the Euler-Angles in the "ZX'Z''"-convention from a rotation matrix R (that is, R has orthogonal and unit-length column (or equivalently row) vectors). 

	The method returns a vector Vec3f v of three floating point values, such that with the terminology, 
	alpha = v.x
	beta = v.y,
	gamma = v.z, 

	it holds that 
	
	R = R_z(gamma) * R_x(beta) * R_z(alpha),
	
	where R_x(a), R_y(a), R_z(a) denote the following matrices, representing a rotation of an angle a around the x, y, respectively the z axis:

	R_x(a) = |1 	0      	0	   |
			 |0 	cos(x) 	-sin(x)|
			 |0		sin(x)	cos(x) |	

	R_y(a) = |cos(x) 	0	sin(x)|
			 |0 		1 	0	  |
			 |-sin(x)	0	cos(x)|

	R_z(a) = |cos(x) 	-sin(x)	0 |
			 |sin(x) 	cos(x) 	0 |
			 |0			0		1 |.

	The angles alpha, beta, gamma are not unique.
*/
Vec3f ZXZ_angles_from_rotation_matrix(const Matrix3x3f& R) {
	float alpha = 0.0f;
	float beta = 0.0f;
	float gamma = 0.0f;

	// R_33
	if(R(2,2) == 1.0f) {
		beta = 0.0f;
		if(R(0,0) == 0.0f) {
			gamma = 0.0f;
			alpha = M_PI_2;
		} else {
			gamma = 0.0f; // arbitrary value, hence we let the -gamma below stay, so that we dont forget it if we change this arbitrary value later
			// R_21, R_11
			alpha = -gamma + atan2(R(1,0), R(0,0));
		} 
	} else if(R(2,2) == -1.0f) {
		beta = 3 * M_PI_2; // 3/2 pi
		// R_12
		if(R(0,1) == 0.0f) {
			alpha = 0.0f;
			gamma = 0.0f;
		} else {
			gamma = 0.0f;
			// R_11, R_12
			alpha = -gamma - M_PI_2 + atan2(-R(0,0), R(0,1));
		}
	} else { // non degenerate case
		beta = acos(R(2,2));
		// R_32
		if(R(2, 1) == 0.0f) {
			gamma = M_PI_2;
		} else {
			// R_31, R_32
			gamma = atan2(R(2, 0), R(2, 1));
		}

		if(R(1, 2) == 0.0f) {
			alpha = M_PI_2;
		} else {
			// R_13, R_23
			alpha = atan2(-R(0, 2), R(1, 2));
		}
	}

	return Vec3f(alpha, beta, gamma);
};


Vec3f RPY_angles_from_rotation_matrix(const Matrix3x3f& R) {
	float alpha = 0.0f;
	float beta = 0.0f;
	float gamma = 0.0f;

	// R_31
	if(R(2,0) == 1.0f) {
		beta = 3 * M_PI_2; // 3/2 pi
		// R_13
		if(R(0, 2) == 0.0f) {
			gamma = 0.0f;
			alpha = M_PI_2;
		} else {
			gamma = 0.0f; // arbitrary value, hence we let the -gamma below stay, so that we dont forget it if we change this arbitrary value later
			// R_12, R_13
			alpha = -gamma + atan2(R(0, 1), R(0, 2));
		} 
		//R_31
	} else if(R(2, 0) == -1.0f) {
		beta = M_PI_2; // pi/2
		// R_13
		if(R(0, 2) == 0.0f) {
			gamma = 0.0f;
			alpha = M_PI_2;
		} else {
			gamma = 0.0f;
			// R_12, R_13
			alpha = gamma + atan2(R(0, 1), R(0, 2));
		}
	} else { // non degenerate case
		beta = asin(-R(2, 0));
		// R_33
		if(R(2, 2) == 0.0f) {
			alpha = M_PI_2;
		} else {
			// R_32, R_33
			alpha = atan2(R(2, 1), R(2, 2));
		}
		// R_11
		if(R(0,0) == 0.0f) {
			gamma = M_PI_2;
		} else {
			// R_21, R_11
			gamma = atan2(R(1, 0), R(0, 0));
		}
	}

	return Vec3f(alpha, beta, gamma);
}

Matrix3x3f get_rotation_matrix_around_X_axis(float theta) {
	Matrix3x3f R;

	float c = cos(theta);
	float s = sin(theta);

	return Matrix3x3f(1.0f, 0.0f, 0.0f, 
	                  0.0f, c, -s, 
	                  0.0f, s, c);
}


Matrix3x3f get_rotation_matrix_around_Y_axis(float theta) {
	Matrix3x3f R;

	float c = cos(theta);
	float s = sin(theta);

	return Matrix3x3f(c, 0.0f, s, 0.0f, 
	                  1.0f, 0.0f, 
	                  -s, 0.0f, c);
}

Matrix3x3f get_rotation_matrix_around_Z_axis(float theta) {
	Matrix3x3f R;

	float c = cos(theta);
	float s = sin(theta);

	return Matrix3x3f(c, -s, 0.0f, 
	                  s, c, 0.0f, 
	                  0.0f, 0.0f, 1.0f);
}