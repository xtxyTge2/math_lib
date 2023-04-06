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

	Vec3f ZXZ_angles = ZXZ_angles_from_rotation_matrix(R);

	std::cout << "alpha: " << ZXZ_angles.x << "\nbeta: " << ZXZ_angles.y << "\ngamma: " << ZXZ_angles.z << std::endl;

	std::cout << "\n";

	Vec3f RPY_angles = RPY_angles_from_rotation_matrix(R);

	std::cout << "alpha: " << RPY_angles.x << "\nbeta: " << RPY_angles.y << "\ngamma: " << RPY_angles.z << std::endl;

	return 0;
}