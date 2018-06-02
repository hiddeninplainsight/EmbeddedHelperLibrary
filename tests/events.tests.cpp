#include <ehl/events.h>
#include <unity_cpp.h>

namespace
{
	int globalVoidEventHandlerCallCount;

	void GlobalVoidEventHandler()
	{
		++globalVoidEventHandlerCallCount;
	}

	int globalParameterEventHandlerValue;

	void GlobalIntEventHandler(int value)
	{
		globalParameterEventHandlerValue = value;
	}
}

TEST_GROUP(events_tests);
TEST_SETUP(events_tests)
{
	globalVoidEventHandlerCallCount = 0;
	globalParameterEventHandlerValue = 0;
}
TEST_TEAR_DOWN(events_tests)
{
}

class events_tests_state
{
public:
	int voidEventHandlerCallCount{0};
	void VoidEventHandler()
	{
		++voidEventHandlerCallCount;
	}

	int intEventHandlerValue{0};
	void IntEventHandler(int value)
	{
		intEventHandlerValue = value;
	}
};

TEST(events_tests, A_global_void_event_handler_can_be_raised_by_void_event)
{
	ehl::event<void> event;
	ehl::event_handler<void, void> handler(GlobalVoidEventHandler);

	event.set_handler(&handler);

	event.raise();

	TEST_ASSERT_EQUAL_INT(1, globalVoidEventHandlerCallCount);
}

TEST(events_tests, A_class_void_event_handler_can_be_raised_by_void_event)
{
	events_tests_state state;
	ehl::event<void> event;
	ehl::event_handler<events_tests_state, void> handler(state, &events_tests_state::VoidEventHandler);

	event.set_handler(&handler);

	event.raise();

	TEST_ASSERT_EQUAL_INT(1, state.voidEventHandlerCallCount);
}


TEST(events_tests, A_global_event_handler_with_a_parameter_can_be_raised_by_event_with_a_matching_parameter)
{
	ehl::event<int> event;
	ehl::event_handler<void, int> handler(GlobalIntEventHandler);

	event.set_handler(&handler);

	event.raise(10);

	TEST_ASSERT_EQUAL_INT(10, globalParameterEventHandlerValue);
}

TEST(events_tests, A_class_event_handler_with_a_parameter_can_be_raised_by_event_with_a_matching_parameter)
{
	events_tests_state state;
	ehl::event<int> event;
	ehl::event_handler<events_tests_state, int> handler(state, &events_tests_state::IntEventHandler);

	event.set_handler(&handler);

	event.raise(20);

	TEST_ASSERT_EQUAL_INT(20, state.intEventHandlerValue);
}
