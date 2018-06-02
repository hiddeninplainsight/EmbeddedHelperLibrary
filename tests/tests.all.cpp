#include "unity_cpp.h"

TEST_GROUP_RUNNER(fast_exponential_smoothing)
{
	RUN_TEST_CASE(fast_exponential_smoothing, No_smoothing_gives_back_the_value_passed_in);
	RUN_TEST_CASE(fast_exponential_smoothing, The_first_value_is_smoothed);
}

TEST_GROUP_RUNNER(exponential_smoothing)
{
	RUN_TEST_CASE(exponential_smoothing, A_smoothing_factor_of_1_applies_no_smoothing);
	RUN_TEST_CASE(exponential_smoothing, A_smoothing_factor_of_0_5_smoothes_the_data);
	RUN_TEST_CASE(exponential_smoothing, A_integer_type_can_be_smoothed_by_a_factor_of_0_5);
	RUN_TEST_CASE(exponential_smoothing, exponential_smoothing_can_be_passed_to_algorithms);
}

TEST_GROUP_RUNNER(span)
{
	RUN_TEST_CASE(span, A_span_initialised_from_a_C_style_array_covers_the_entire_array);
	RUN_TEST_CASE(span, A_span_initialised_from_two_pointers);
	RUN_TEST_CASE(span, A_span_can_be_copied);
	RUN_TEST_CASE(span, A_span_can_be_copied_to_a_const_version_of_itself);
	RUN_TEST_CASE(span, An_already_initialised_span_can_have_another_one_copied_over_it);
}

static void RunAllTests()
{
	RUN_TEST_GROUP(fast_exponential_smoothing);
	RUN_TEST_GROUP(exponential_smoothing);
	RUN_TEST_GROUP(span);
}

int TestMain(int argc, char** argv)
{
	return UnityMain(argc, const_cast<const char**>(argv), RunAllTests);
}
