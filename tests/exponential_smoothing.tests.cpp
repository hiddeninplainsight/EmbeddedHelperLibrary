#include <ehl/exponential_smoothing.h>
#include <unity_cpp.h>

#include <ehl/algorithm.h>

TEST_GROUP(exponential_smoothing);
TEST_SETUP(exponential_smoothing)
{
}
TEST_TEAR_DOWN(exponential_smoothing)
{
}

TEST(exponential_smoothing, A_smoothing_factor_of_1_applies_no_smoothing)
{
	ehl::exponential_smoothing<float> smoothed(1.0f);

	smoothed.add_value(10);
	TEST_ASSERT_EQUAL_FLOAT(10, smoothed.value());

	smoothed.add_value(20);
	TEST_ASSERT_EQUAL_FLOAT(20, smoothed.value());
}

TEST(exponential_smoothing, A_smoothing_factor_of_0_5_smoothes_the_data)
{
	ehl::exponential_smoothing<float> smoothed(0.5f);

	smoothed.add_value(10);
	TEST_ASSERT_EQUAL_FLOAT(5, smoothed.value());

	smoothed.add_value(10);
	TEST_ASSERT_EQUAL_FLOAT(7.5, smoothed.value());
}

TEST(exponential_smoothing, A_integer_type_can_be_smoothed_by_a_factor_of_0_5)
{
	ehl::exponential_smoothing<int> smoothed(5, 10);

	smoothed.add_value(10);
	TEST_ASSERT_EQUAL_INT(5, smoothed.value());

	smoothed.add_value(10);
	TEST_ASSERT_EQUAL_INT(7, smoothed.value());
}

TEST(exponential_smoothing, exponential_smoothing_can_be_passed_to_algorithms)
{
	ehl::exponential_smoothing<float> smoothed(0.75);

	float const original[3] = {10.0f, 5.0f, 10.0f};
	float smoothed_data[3] = {0.0f};

	ehl::transform(original, original + 3, smoothed_data, smoothed);

	TEST_ASSERT_EQUAL_FLOAT(7.5f, smoothed_data[0]);
	TEST_ASSERT_EQUAL_FLOAT(5.625f, smoothed_data[1]);
	TEST_ASSERT_EQUAL_FLOAT(8.90625f, smoothed_data[2]);
}
