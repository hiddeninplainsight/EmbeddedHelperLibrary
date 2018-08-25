#include <ehl/either.h>
#include <unity_cpp.h>

TEST_GROUP(either_tests);
TEST_SETUP(either_tests)
{
}
TEST_TEAR_DOWN(either_tests)
{
}


TEST(either_tests, An_uninitialised_either_is_neither_of_the_types_it_stores)
{
	ehl::either<int, long> target;

	TEST_ASSERT_FALSE(target.is<int>());
	TEST_ASSERT_FALSE(target.is<long>());
}

TEST(either_tests, Settings_a_value_matching_the_first_type_makes_the_either_represent_that_type)
{
	ehl::either<int, long> target;

	target.set(static_cast<int>(1));

	TEST_ASSERT_TRUE(target.is<int>());
	TEST_ASSERT_FALSE(target.is<long>());
}

TEST(either_tests, Settings_a_value_matching_the_second_type_makes_the_either_represent_that_type)
{
	ehl::either<int, long> target;

	target.set(static_cast<long>(1));

	TEST_ASSERT_FALSE(target.is<int>());
	TEST_ASSERT_TRUE(target.is<long>());
}

TEST(either_tests, The_set_value_can_be_retrieved)
{
	ehl::either<int, long> target;

	target.set(static_cast<long>(24));

	TEST_ASSERT_EQUAL(24, static_cast<long>(target));

	target.set(static_cast<int>(32));

	TEST_ASSERT_EQUAL(32, static_cast<int>(target));
}

namespace
{
	struct counter
	{
		int* count;
		explicit counter(int* count)
			: count{count}
		{
		}

		counter(counter const& other)
			: count{other.count}
		{
			++*count;
		}

		~counter()
		{
			--*count;
		}
	};
}

TEST(either_tests, An_object_that_has_been_set_is_destroyed_when_a_different_type_value_is_set)
{
	ehl::either<counter, long> target;
	int count{0};
	counter c{&count};

	target.set(c);

	target.set(static_cast<long>(32));

	TEST_ASSERT_EQUAL(0, count);
}

TEST(either_tests, An_object_that_has_been_set_as_the_second_type_is_destroyed_when_a_different_type_value_is_set)
{
	ehl::either<long, counter> target;
	int count{0};
	counter c{&count};

	target.set(c);

	target.set(static_cast<long>(32));

	TEST_ASSERT_EQUAL(0, count);
}

