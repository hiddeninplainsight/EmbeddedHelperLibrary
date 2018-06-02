#include "unity_cpp.h"

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
	RUN_TEST_GROUP(span);
}

int TestMain(int argc, char** argv)
{
	return UnityMain(argc, const_cast<const char**>(argv), RunAllTests);
}
