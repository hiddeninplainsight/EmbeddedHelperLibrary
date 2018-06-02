#include <ehl/fast_exponential_smoothing.h>
#include <stdint.h>
#include <unity_cpp.h>

TEST_GROUP(fast_exponential_smoothing);
TEST_SETUP(fast_exponential_smoothing)
{
}
TEST_TEAR_DOWN(fast_exponential_smoothing)
{
}

TEST(fast_exponential_smoothing, No_smoothing_gives_back_the_value_passed_in)
{
	ehl::fast_exponential_smoothing<0, uint16_t, uint32_t> smoothing;

	smoothing.add_value(10);

	TEST_ASSERT_EQUAL_UINT16(10, smoothing.value());
}

TEST(fast_exponential_smoothing, The_first_value_is_smoothed)
{
	ehl::fast_exponential_smoothing<3, uint16_t, uint32_t> smoothing;

	smoothing.add_value(512);

	// 512 >> 3 == 64
	TEST_ASSERT_EQUAL_UINT16(64, smoothing.value());
}

TEST(fast_exponential_smoothing, The_second_value_is_smoothed_and_includes_part_of_the_first_value)
{
	ehl::fast_exponential_smoothing<3, uint16_t, uint32_t> smoothing;

	smoothing.add_value(512);
	smoothing.add_value(512);

	// stored = 512 (from first value)
	// (stored - (stored >> 3) + 512) >> 3 == 120
	TEST_ASSERT_EQUAL_UINT16(120, smoothing.value());
}
