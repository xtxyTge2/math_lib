#include <iostream>
#include "rotations.hpp"


int main(int argc, char** argv) {
	
	Matrix3x3f R; 
	R.data[0] = 0.36f;
	R.data[1] = 0.48f;
	R.data[2] = -0.8f;

	R.data[3] = -0.8f;
	R.data[4] = 0.6f;
	R.data[5] = 0.0f;

	R.data[6] = 0.48f;
	R.data[7] = 0.64f;
	R.data[8] = 0.6f;

	Vec3f ZYZ_angles = ZYZ_angles_from_rotation_matrix(R);

	std::cout << "alpha: " << ZYZ_angles.x << "\nbeta: " << ZYZ_angles.y << "\ngamma: " << ZYZ_angles.z << std::endl;

	return 0;
}