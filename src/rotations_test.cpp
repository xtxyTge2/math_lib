#include <iostream>
#include <cmath>
#include "rotations.hpp"

#include "gtest/gtest.h"
namespace {

	TEST(RPY_angles_from_rotation_matrix_test, generic_matrix_angles_hand_calculated) {
		Matrix3x3f R = {0.36f, 0.48f, -0.8f, 
						-0.8f, 0.6f, 0.0f, 
						0.48f, 0.64f, 0.6f};

		Vec3f RPY_angles = RPY_angles_from_rotation_matrix(R);

		float alpha = RPY_angles.x;
		float beta = RPY_angles.y;
		float gamma = RPY_angles.z;

		EXPECT_FLOAT_EQ(alpha, atan2(0.64, 0.6));
		EXPECT_FLOAT_EQ(beta, asin(-0.48f));
		EXPECT_FLOAT_EQ(gamma, atan2(-0.8, 0.36));
	}

	TEST(RPY_angles_from_rotation_matrix_test, generic_matrix_factors_correctly) {
		Matrix3x3f R = {0.36f, 0.48f, -0.8f, 
		-0.8f, 0.6f, 0.0f, 
		0.48f, 0.64f, 0.6f};

		Vec3f RPY_angles = RPY_angles_from_rotation_matrix(R);

		float alpha = RPY_angles.x;
		float beta = RPY_angles.y;
		float gamma = RPY_angles.z;

		float alpha_expected = atan2(0.64, 0.6);
		float beta_expected = asin(-0.48f);
		float gamma_expected = atan2(-0.8, 0.36);

		EXPECT_FLOAT_EQ(alpha, alpha_expected);
		EXPECT_FLOAT_EQ(beta, beta_expected);
		EXPECT_FLOAT_EQ(gamma, gamma_expected);

		Matrix3x3f R_x = get_rotation_matrix_around_X_axis(alpha);
		Matrix3x3f R_y = get_rotation_matrix_around_Y_axis(beta);
		Matrix3x3f R_z = get_rotation_matrix_around_Z_axis(gamma);

		Matrix3x3f R_x_expected = get_rotation_matrix_around_X_axis(alpha_expected);
		Matrix3x3f R_y_expected = get_rotation_matrix_around_Y_axis(beta_expected);
		Matrix3x3f R_z_expected = get_rotation_matrix_around_Z_axis(gamma_expected);

		// tests if the rotation matrix R factors into the product R_z * R_y * R_x, where R_x, R_y, R_z are the standard rotation matrices around the x, y and respectively z axix with corresponding rotation angles alpha, beta, and respectively gamma.


		// test if rotation matrix around x axis is correct
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < 3; c++) {
				EXPECT_FLOAT_EQ(R_x(r, c), R_x_expected(r, c)) << " matrix differs from expected matrix at position " << r << ", " << c << "\n";
			}
		}

		// test if rotation matrix around y axis is correct
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < 3; c++) {
				EXPECT_FLOAT_EQ(R_y(r, c), R_y_expected(r, c)) << " matrix differs from expected matrix at position " << r << ", " << c << "\n";
			}
		}

		// test if rotation matrix around z axis is correct
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < 3; c++) {
				EXPECT_FLOAT_EQ(R_z(r, c), R_z_expected(r, c)) << " matrix differs from expected matrix at position " << r << ", " << c << "\n";
			}
		}


		// rendundant check, but just to be absolutely sure that the product of the rotation matrices yields our initial rotation matrix, in other words we do a sanity check that we factored correctly.
		Matrix3x3f R_result = R_z * R_y * R_x;
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < 3; c++) {
				EXPECT_NEAR(R(r, c), R_result(r, c), 1e-7) << " matrix differs from expected matrix at position " << r << ", " << c << "\n R:\n" << R.to_string() << "\n" << "R_result:\n" << R_result.to_string() << "\n";
			}
		}
	}

} // namespace
