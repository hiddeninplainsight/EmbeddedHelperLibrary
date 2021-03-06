
add_executable(ehl.tests
	main.cpp
	tests.all.cpp
	meta/literal_parser.tests.cpp
	meta/metafunctions.tests.cpp
	type_traits/copy_assign_t.tests.cpp
	type_traits/detection_compiler_generated_methods.test_types.cpp
	type_traits/detection_compiler_generated_methods.test_types.h
	type_traits/detection_idiom.tests.cpp
	type_traits/is_container.tests.cpp
	type_traits/size_type_t.tests.cpp
	either.tests.cpp
	events.tests.cpp
	exponential_smoothing.tests.cpp
	fast_exponential_smoothing.tests.cpp
	isr_circular_buffer.tests.cpp
	isr_read_variable.tests.cpp
	isr_written_variable.tests.cpp
	linear_interpolator.tests.cpp
	optional.tests.cpp
	recorded_operations.cpp
	recorded_operations.h
	rolling_average.tests.cpp
	rolling_average_with_events.tests.cpp
	safe_type.tests.cpp
	span.tests.cpp
	)

add_custom_command(TARGET ehl.tests
	PRE_BUILD
	COMMAND cd ${CMAKE_CURRENT_LIST_DIR} && ruby ../Unity/auto/generate_fixture_runner.rb tests.all.cpp
	)

target_link_libraries(ehl.tests # Libraries for testing
	ehl::unity
	)

target_link_libraries(ehl.tests
	EmbeddedHelperLibrary
	)
