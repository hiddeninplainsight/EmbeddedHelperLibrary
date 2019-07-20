#include <ehl/isr_circular_buffer.h>
#include <unity_cpp.h>

TEST_GROUP(isr_circular_buffer_tests);
TEST_SETUP(isr_circular_buffer_tests)
{
}
TEST_TEAR_DOWN(isr_circular_buffer_tests)
{
}

TEST(isr_circular_buffer_tests, The_buffer_is_initially_empty)
{
	ehl::isr_circular_buffer<char, 4> buffer;

	TEST_ASSERT_EQUAL_INT(0, buffer.length());
}

TEST(isr_circular_buffer_tests, Pushing_a_value_to_a_buffer_increments_its_length)
{
	ehl::isr_circular_buffer<char, 4> buffer;

	TEST_ASSERT_TRUE(buffer.push('A'));

	TEST_ASSERT_EQUAL_INT(1, buffer.length());
}

TEST(isr_circular_buffer_tests, A_pushed_value_can_be_read_back)
{
	ehl::isr_circular_buffer<char, 4> buffer;

	buffer.push('B');

	auto readValue = buffer.pop();

	TEST_ASSERT_TRUE(readValue.valid);
	TEST_ASSERT_EQUAL('B', readValue.value);

	TEST_ASSERT_EQUAL(0, buffer.length());
}

TEST(isr_circular_buffer_tests, Popping_an_empty_value_gives_an_invalid_value)
{
	ehl::isr_circular_buffer<char, 4> buffer;

	auto readValue = buffer.pop();

	TEST_ASSERT_FALSE(readValue.valid);
}

TEST(isr_circular_buffer_tests, You_cannot_push_more_values_than_the_buffer_can_hold)
{
	ehl::isr_circular_buffer<char, 4> buffer;

	TEST_ASSERT_TRUE(buffer.push('A'));
	TEST_ASSERT_TRUE(buffer.push('B'));
	TEST_ASSERT_TRUE(buffer.push('C'));
	TEST_ASSERT_FALSE(buffer.push('D'));

	auto readValue = buffer.pop();
	TEST_ASSERT_TRUE(readValue.valid);
	TEST_ASSERT_EQUAL('A', readValue.value);
}

TEST(isr_circular_buffer_tests, Pushing_and_popping_values_when_the_buffer_should_wrap)
{
	ehl::isr_circular_buffer<int, 4> buffer;

	TEST_ASSERT_TRUE(buffer.push('A'));
	TEST_ASSERT_TRUE(buffer.push('B'));
	TEST_ASSERT_TRUE(buffer.push('C'));

	auto readValue = buffer.pop();
	TEST_ASSERT_TRUE(readValue.valid);
	TEST_ASSERT_EQUAL('A', readValue.value);

	TEST_ASSERT_TRUE(buffer.push('D'));
}

TEST(isr_circular_buffer_tests, The_length_is_still_correct_after_the_buffer_has_wrapped)
{
	ehl::isr_circular_buffer<int, 4> buffer;

	buffer.push('A');
	buffer.push('B');
	buffer.push('C');
	buffer.pop();
	buffer.push('D');

	TEST_ASSERT_EQUAL(3, buffer.length());
}

TEST(isr_circular_buffer_tests, Popping_values_pushed_after_the_buffer_has_wrapped)
{
	ehl::isr_circular_buffer<int, 4> buffer;

	buffer.push('A');
	buffer.push('B');
	buffer.push('C');
	buffer.pop();
	buffer.pop();
	buffer.push('D');
	buffer.push('E');
	buffer.pop();
	buffer.pop();
	auto readValue = buffer.pop();

	TEST_ASSERT_TRUE(readValue.valid);
	TEST_ASSERT_EQUAL('E', readValue.value);
	TEST_ASSERT_EQUAL(0, buffer.length());
}
