#include <ehl/isr_read_variable.h>
#include <unity_cpp.h>

TEST_GROUP(isr_read_variable_tests);
TEST_SETUP(isr_read_variable_tests)
{
}
TEST_TEAR_DOWN(isr_read_variable_tests)
{
}

int returns_35();

TEST(isr_read_variable_tests, The_value_written_to_an_isr_read_variable_can_be_read_back)
{
	ehl::isr_read_variable<int> variable;

	variable = 10;
	TEST_ASSERT_EQUAL_INT(10, variable);

	variable = 20;
	TEST_ASSERT_EQUAL_INT(20, variable);
}

TEST(isr_read_variable_tests, An_isr_read_variable_can_be_set_using_an_rvalue)
{
	ehl::isr_read_variable<int> variable;

	variable = returns_35();
	TEST_ASSERT_EQUAL_INT(35, variable);
}

TEST(isr_read_variable_tests, An_isr_read_variable_can_have_an_initial_value_set)
{
	ehl::isr_read_variable<int> variable_a = 100;
	TEST_ASSERT_EQUAL_INT(100, variable_a);

	ehl::isr_read_variable<int> variable_b{200};
	TEST_ASSERT_EQUAL_INT(200, variable_b);
}

TEST(isr_read_variable_tests, An_isr_read_variable_can_be_copied_to_another_isr_read_variable)
{
	ehl::isr_read_variable<int> variable_a = 100;
	ehl::isr_read_variable<int> variable_b = variable_a;
	TEST_ASSERT_EQUAL_INT(100, variable_b);

	ehl::isr_read_variable<int> variable_c = 1;
	ehl::isr_read_variable<int> variable_d = variable_c;
	TEST_ASSERT_EQUAL_INT(1, variable_d);
}

TEST(isr_read_variable_tests, A_const_isr_read_variable_can_be_read)
{
	ehl::isr_read_variable<int> const variable = 50;

	TEST_ASSERT_EQUAL_INT(50, variable);
}
