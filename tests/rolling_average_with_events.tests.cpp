#include <ehl/rolling_average_with_event.h>
#include <unity_cpp.h>

TEST_GROUP(rolling_average_with_event);
TEST_SETUP(rolling_average_with_event)
{
}
TEST_TEAR_DOWN(rolling_average_with_event)
{
}


namespace
{
	int averageFromEvent;
	void average_update_handler(int value) { averageFromEvent = value; }
}

TEST(rolling_average_with_event, An_event_is_raised_when_a_value_is_added)
{
	ehl::rolling_average_with_event<int, 3> average;

	// Attach event handler
	ehl::event_handler<void, int> handler(average_update_handler);
	average.average_update.set_handler(&handler);

	// Reset global test value
	averageFromEvent = 0;

	average.add_value(30);

	TEST_ASSERT_EQUAL_INT(10, averageFromEvent);
}

