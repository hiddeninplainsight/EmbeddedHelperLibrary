
add_executable(ehl.tests
	main.cpp
	tests.all.cpp
	meta/literal_parser.tests.cpp
	meta/metafunctions.tests.cpp
	events.tests.cpp
	exponential_smoothing.tests.cpp
	fast_exponential_smoothing.tests.cpp
	linear_interpolator.tests.cpp
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
