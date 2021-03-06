#include <ehl/either.h>
#include <ehl/rvalue.h>

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

	TEST_ASSERT_EQUAL(24, target.as<long>());

	target.set(static_cast<int>(32));

	TEST_ASSERT_EQUAL(32, target.as<int>());
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

TEST(either_tests, An_object_that_has_been_set_is_destroyed_when_the_either_is_destroyed)
{
	int count{0};
	counter c{&count};

	{
		ehl::either<long, counter> target;
		target.set(c);
	}

	TEST_ASSERT_EQUAL(0, count);
}

TEST(either_tests, An_object_that_has_been_set_can_be_move_constructed)
{
	int count{0};
	counter c{&count};

	{
		ehl::either<long, counter> target;
		target.set(c);

		ehl::either<long, counter> moved_to{::ehl::as_rvalue(target)};
	}

	TEST_ASSERT_EQUAL(0, count);
}

TEST(either_tests, An_object_that_has_been_set_can_be_move_using_operator_assignment)
{
	int count{0};
	counter c{&count};

	{
		ehl::either<long, counter> target;

		{
			ehl::either<long, counter> move_from{::ehl::as_rvalue(target)};
			move_from.set(c);

			target = ::ehl::as_rvalue(move_from);
		}
	}

	TEST_ASSERT_EQUAL(0, count);
}

namespace
{
	struct move_only
	{
		move_only() = default;
		move_only(move_only const&) = delete;
		move_only(move_only&&) = default;
	};
}

TEST(either_tests, An_object_can_be_moved_into_the_either)
{
	ehl::either<long, move_only> target;

	move_only object;

	target.set(::ehl::as_rvalue(object));

	// If this compiles it passes
}
