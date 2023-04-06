#include "rotations.hpp"


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
	if(R.data[8] == 1.0f) {
		beta = 0.0f;
		// R_11 = R[0][0] // care with 0 indices etc! R_11 is actually R[0][0] probably!
		if(R.data[0] == 0.0f) {
			gamma = 0.0f;
			alpha = M_PI_2;
		} else {
			gamma = 0.0f; // arbitrary value, hence we let the -gamma below stay, so that we dont forget it if we change this arbitrary value later
			// R_21, R_11
			alpha = -gamma + atan2(R.data[3], R.data[0]);
		} 
	} else if(R.data[8] == -1.0f) {
		beta = 3 * M_PI_2; // 3/2 pi
		// R_12
		if(R.data[1] == 0.0f) {
			alpha = 0.0f;
			gamma = 0.0f;
		} else {
			gamma = 0.0f;
			// R_11, R_12
			alpha = -gamma - M_PI_2 + atan2(-R.data[0], R.data[1]);
		}
	} else { // non degenerate case
		beta = acos(R.data[8]);
		// R_32
		if(R.data[7] == 0.0f) {
			gamma = M_PI_2;
		} else {
			// R_31, R_32
			gamma = atan2(R.data[6], R.data[7]);
		}

		if(R.data[6] == 0.0f) {
			alpha = M_PI_2;
		} else {
			// R_13, R_23
			alpha = atan2(-R.data[2], R.data[6]);
		}
	}

	return Vec3f(alpha, beta, gamma);
};


Vec3f RPY_angles_from_rotation_matrix(const Matrix3x3f& R) {
	float alpha = 0.0f;
	float beta = 0.0f;
	float gamma = 0.0f;

	// R_31
	if(R.data[6] == 1.0f) {
		beta = 3 * M_PI_2; // 3/2 pi
		// R_13
		if(R.data[2] == 0.0f) {
			gamma = 0.0f;
			alpha = M_PI_2;
		} else {
			gamma = 0.0f; // arbitrary value, hence we let the -gamma below stay, so that we dont forget it if we change this arbitrary value later
			// R_12, R_13
			alpha = -gamma + atan2(R.data[1], R.data[2]);
		} 
		//R_31
	} else if(R.data[6] == -1.0f) {
		beta = M_PI_2; // pi/2
		// R_13
		if(R.data[2] == 0.0f) {
			gamma = 0.0f;
			alpha = M_PI_2;
		} else {
			gamma = 0.0f;
			// R_12, R_13
			alpha = gamma + atan2(R.data[1], R.data[2]);
		}
	} else { // non degenerate case
		beta = asin(-R.data[6]);
		// R_33
		if(R.data[8] == 0.0f) {
			alpha = M_PI_2;
		} else {
			// R_32, R_33
			alpha = atan2(R.data[7], R.data[8]);
		}
		// R_11
		if(R.data[0] == 0.0f) {
			gamma = M_PI_2;
		} else {
			// R_21, R_11
			gamma = atan2(R.data[3], R.data[0]);
		}
	}

	return Vec3f(alpha, beta, gamma);
}

Matrix3x3f get_rotation_matrix_around_X_axis(float theta) {
	Matrix3x3f R;

	float c = cos(theta);
	float s = sin(theta);

	// first row
	R.data[0] = 1.0f;
	R.data[1] = 0.0f;
	R.data[2] = 0.0f;
	
	// second row
	R.data[3] = 0.0f;
	R.data[4] = c;
	R.data[5] = -s;

	// third row
	R.data[6] = 0.0f;
	R.data[7] = s;
	R.data[8] = c;

	return R;
}


Matrix3x3f get_rotation_matrix_around_Y_axis(float theta) {
	Matrix3x3f R;

	float c = cos(theta);
	float s = sin(theta);

	// first row
	R.data[0] = c;
	R.data[1] = 0.0f;
	R.data[2] = s;
	
	// second row
	R.data[3] = 0.0f;
	R.data[4] = 1.0f;
	R.data[5] = 0.0f;

	// third row
	R.data[6] = -s;
	R.data[7] = 0.0f;
	R.data[8] = c;

	return R;
}

Matrix3x3f get_rotation_matrix_around_Z_axis(float theta) {
	Matrix3x3f R;

	float c = cos(theta);
	float s = sin(theta);

	// first row
	R.data[0] = c;
	R.data[1] = -s;
	R.data[2] = 0.0f;
	
	// second row
	R.data[3] = s;
	R.data[4] = c;
	R.data[5] = 0.0f;

	// third row
	R.data[6] = 0.0f;
	R.data[7] = 0.0f;
	R.data[8] = 1.0f;

	return R;
}