#include "unity_cpp.h"

TEST_GROUP_RUNNER(exponential_smoothing)
{
	RUN_TEST_CASE(exponential_smoothing, A_smoothing_factor_of_1_applies_no_smoothing);
	RUN_TEST_CASE(exponential_smoothing, A_smoothing_factor_of_0_5_smoothes_the_data);
	RUN_TEST_CASE(exponential_smoothing, A_integer_type_can_be_smoothed_by_a_factor_of_0_5);
	RUN_TEST_CASE(exponential_smoothing, exponential_smoothing_can_be_passed_to_algorithms);
}

TEST_GROUP_RUNNER(fast_exponential_smoothing)
{
	RUN_TEST_CASE(fast_exponential_smoothing, No_smoothing_gives_back_the_value_passed_in);
	RUN_TEST_CASE(fast_exponential_smoothing, The_first_value_is_smoothed);
	RUN_TEST_CASE(fast_exponential_smoothing, The_second_value_is_smoothed_and_includes_part_of_the_first_value);
}

TEST_GROUP_RUNNER(isr_written_variable_tests)
{
	RUN_TEST_CASE(isr_written_variable_tests, The_value_written_to_an_isr_written_variable_can_be_read_back);
	RUN_TEST_CASE(isr_written_variable_tests, An_isr_written_variable_can_be_set_using_an_rvalue);
	RUN_TEST_CASE(isr_written_variable_tests, An_isr_written_variable_can_have_an_initial_value_set);
	RUN_TEST_CASE(isr_written_variable_tests, An_isr_written_variable_can_be_copied_to_another_isr_written_variable);
	RUN_TEST_CASE(isr_written_variable_tests, A_const_isr_written_variable_can_be_read);
}

TEST_GROUP_RUNNER(safe_type)
{
	RUN_TEST_CASE(safe_type, underlying_value_can_be_read);
	RUN_TEST_CASE(safe_type, pre_increment_safe_types);
	RUN_TEST_CASE(safe_type, adding_safe_types);
	RUN_TEST_CASE(safe_type, can_copy_construct_an_lvalue);
	RUN_TEST_CASE(safe_type, can_assign_to_lvalue_but_not_to_rvalue_of_safe_types);
	RUN_TEST_CASE(safe_type, subtracting_safe_types);
	RUN_TEST_CASE(safe_type, comparing_safe_types);
	RUN_TEST_CASE(safe_type, implicit_converting_safe_types);
	RUN_TEST_CASE(safe_type, adding_multiple_operations);
	RUN_TEST_CASE(safe_type, operations_do_not_slice_extendable_objects);
	RUN_TEST_CASE(safe_type, range_limit_cannot_be_exceeded_for_safe_types);
	RUN_TEST_CASE(safe_type, range_limit_cannot_be_exceeded_for_derived_safe_types);
}

TEST_GROUP_RUNNER(linear_interpolator_tests)
{
	RUN_TEST_CASE(linear_interpolator_tests, Interpolating_a_value_matching_one_of_the_x_coordinates_returns_the_matching_y_coordinate);
	RUN_TEST_CASE(linear_interpolator_tests, Interpolating_a_value_in_the_middle_of_the_coordinates_without_a_y_offset);
	RUN_TEST_CASE(linear_interpolator_tests, Interpolating_a_value_in_the_middle_of_the_coordinates_with_a_y_offset);
}

TEST_GROUP_RUNNER(span)
{
	RUN_TEST_CASE(span, A_span_initialised_from_a_C_style_array_covers_the_entire_array);
	RUN_TEST_CASE(span, A_span_initialised_from_two_pointers);
	RUN_TEST_CASE(span, A_span_can_be_copied);
	RUN_TEST_CASE(span, A_span_can_be_copied_to_a_const_version_of_itself);
	RUN_TEST_CASE(span, An_already_initialised_span_can_have_another_one_copied_over_it);
	RUN_TEST_CASE(span, Iterating_a_span_using_const_iterators_allows_reading_but_not_writing);
}

TEST_GROUP_RUNNER(isr_read_variable_tests)
{
	RUN_TEST_CASE(isr_read_variable_tests, The_value_written_to_an_isr_read_variable_can_be_read_back);
	RUN_TEST_CASE(isr_read_variable_tests, An_isr_read_variable_can_be_set_using_an_rvalue);
	RUN_TEST_CASE(isr_read_variable_tests, An_isr_read_variable_can_have_an_initial_value_set);
	RUN_TEST_CASE(isr_read_variable_tests, An_isr_read_variable_can_be_copied_to_another_isr_read_variable);
	RUN_TEST_CASE(isr_read_variable_tests, A_const_isr_read_variable_can_be_read);
}

TEST_GROUP_RUNNER(rolling_average_with_event)
{
	RUN_TEST_CASE(rolling_average_with_event, An_event_is_raised_when_a_value_is_added);
}

TEST_GROUP_RUNNER(rolling_average)
{
	RUN_TEST_CASE(rolling_average, Initial_average_is_zero);
	RUN_TEST_CASE(rolling_average, The_average_of_a_single_value_added_the_same_number_of_times_as_values_in_the_average_is_the_value);
	RUN_TEST_CASE(rolling_average, The_average_of_a_multiple_values_without_rolling);
	RUN_TEST_CASE(rolling_average, Values_added_to_the_average_before_it_rolls_are_not_included_in_the_average_once_it_has_rolled);
	RUN_TEST_CASE(rolling_average, exponential_smoothing_can_be_passed_to_algorithms);
}

TEST_GROUP_RUNNER(either_tests)
{
	RUN_TEST_CASE(either_tests, An_uninitialised_either_is_neither_of_the_types_it_stores);
	RUN_TEST_CASE(either_tests, Settings_a_value_matching_the_first_type_makes_the_either_represent_that_type);
	RUN_TEST_CASE(either_tests, Settings_a_value_matching_the_second_type_makes_the_either_represent_that_type);
	RUN_TEST_CASE(either_tests, The_set_value_can_be_retrieved);
	RUN_TEST_CASE(either_tests, An_object_that_has_been_set_is_destroyed_when_a_different_type_value_is_set);
	RUN_TEST_CASE(either_tests, An_object_that_has_been_set_as_the_second_type_is_destroyed_when_a_different_type_value_is_set);
	RUN_TEST_CASE(either_tests, An_object_that_has_been_set_is_destroyed_when_the_either_is_destroyed);
	RUN_TEST_CASE(either_tests, An_object_that_has_been_set_can_be_move_constructed);
	RUN_TEST_CASE(either_tests, An_object_that_has_been_set_can_be_move_using_operator_assignment);
	RUN_TEST_CASE(either_tests, An_object_can_be_moved_into_the_either);
}

TEST_GROUP_RUNNER(metafunctions)
{
	RUN_TEST_CASE(metafunctions, number_of_digits);
	RUN_TEST_CASE(metafunctions, metastring);
	RUN_TEST_CASE(metafunctions, number_to_string);
}

TEST_GROUP_RUNNER(literal_parser)
{
	RUN_TEST_CASE(literal_parser, Compile_time_checks);
}

TEST_GROUP_RUNNER(events_tests)
{
	RUN_TEST_CASE(events_tests, A_global_void_event_handler_can_be_raised_by_void_event);
	RUN_TEST_CASE(events_tests, A_class_void_event_handler_can_be_raised_by_void_event);
	RUN_TEST_CASE(events_tests, A_global_event_handler_with_a_parameter_can_be_raised_by_event_with_a_matching_parameter);
	RUN_TEST_CASE(events_tests, A_class_event_handler_with_a_parameter_can_be_raised_by_event_with_a_matching_parameter);
}

static void RunAllTests()
{
	RUN_TEST_GROUP(exponential_smoothing);
	RUN_TEST_GROUP(fast_exponential_smoothing);
	RUN_TEST_GROUP(isr_written_variable_tests);
	RUN_TEST_GROUP(safe_type);
	RUN_TEST_GROUP(linear_interpolator_tests);
	RUN_TEST_GROUP(span);
	RUN_TEST_GROUP(isr_read_variable_tests);
	RUN_TEST_GROUP(rolling_average_with_event);
	RUN_TEST_GROUP(rolling_average);
	RUN_TEST_GROUP(either_tests);
	RUN_TEST_GROUP(metafunctions);
	RUN_TEST_GROUP(literal_parser);
	RUN_TEST_GROUP(events_tests);
}

int TestMain(int argc, char** argv)
{
	return UnityMain(argc, const_cast<const char**>(argv), RunAllTests);
}
