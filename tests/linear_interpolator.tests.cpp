#include "ehl/linear_interpolator.h"
#include <unity_cpp.h>

TEST_GROUP(linear_interpolator_tests);
TEST_SETUP(linear_interpolator_tests)
{
}
TEST_TEAR_DOWN(linear_interpolator_tests)
{
}

TEST(linear_interpolator_tests, Interpolating_a_value_matching_one_of_the_x_coordinates_returns_the_matching_y_coordinate)
{
	ehl::linear_interpolator<int, int>::coordinate_type coordinates[] = {
		{0, 0}, {10, 10}};

	ehl::linear_interpolator<int, int> interpolator(coordinates);

	TEST_ASSERT_EQUAL_INT(0, interpolator.interpolate(0));
	TEST_ASSERT_EQUAL_INT(10, interpolator.interpolate(10));
}

TEST(linear_interpolator_tests, Interpolating_a_value_in_the_middle_of_the_coordinates_without_a_y_offset)
{
	ehl::linear_interpolator<int, int>::coordinate_type coordinates[] = {
		{0, 0}, {10, 20}};

	ehl::linear_interpolator<int, int> interpolator(coordinates);

	TEST_ASSERT_EQUAL_INT(10, interpolator.interpolate(5));
}

TEST(linear_interpolator_tests, Interpolating_a_value_in_the_middle_of_the_coordinates_with_a_y_offset)
{
	ehl::linear_interpolator<int, int>::coordinate_type coordinates[] = {
		{0, 10}, {10, 20}};

	ehl::linear_interpolator<int, int> interpolator(coordinates);

	TEST_ASSERT_EQUAL_INT(15, interpolator.interpolate(5));
}
