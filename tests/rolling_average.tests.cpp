#include <ehl/rolling_average.h>
#include <unity_cpp.h>
#include <ehl/algorithm.h>

TEST_GROUP(rolling_average);
TEST_SETUP(rolling_average)
{
}
TEST_TEAR_DOWN(rolling_average)
{
}

TEST(rolling_average, Initial_average_is_zero)
{
	ehl::rolling_average<int, 4> average;

	TEST_ASSERT_EQUAL_INT(0, average);
}

TEST(rolling_average, The_average_of_a_single_value_added_the_same_number_of_times_as_values_in_the_average_is_the_value)
{
	ehl::rolling_average<int, 4> average;

	average.add_value(35);
	average.add_value(35);
	average.add_value(35);
	average.add_value(35);

	TEST_ASSERT_EQUAL_INT(35, average);
}

TEST(rolling_average, The_average_of_a_multiple_values_without_rolling)
{
	ehl::rolling_average<int, 6> average;

	average.add_value(10);
	average.add_value(20);
	average.add_value(30);

	TEST_ASSERT_EQUAL_INT(10, average);
}

TEST(rolling_average, Values_added_to_the_average_before_it_rolls_are_not_included_in_the_average_once_it_has_rolled)
{
	ehl::rolling_average<int, 2> average;

	average.add_value(10);
	average.add_value(20);
	average.add_value(30);

	TEST_ASSERT_EQUAL_INT(25, average);
}

TEST(rolling_average, exponential_smoothing_can_be_passed_to_algorithms)
{
	ehl::rolling_average<float, 3> average;

	float const original[3] = {10.0f, 5.0f, 10.0f};
	float smoothed_data[3] = {0.0f};

	ehl::transform(original, original + 3, smoothed_data, average);

	TEST_ASSERT_FLOAT_WITHIN(0.01f, 3.33f, smoothed_data[0]);
	TEST_ASSERT_FLOAT_WITHIN(0.01f, 5.0f, smoothed_data[1]);
	TEST_ASSERT_FLOAT_WITHIN(0.01f, 8.33f, smoothed_data[2]);
}
