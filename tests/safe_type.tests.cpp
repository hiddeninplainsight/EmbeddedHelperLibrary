#include <ehl/safe_type.h>
#include <unity_cpp.h>
#include <ehl/type_traits/declval.h>
#include <ehl/type_traits/detection_idiom.h>

TEST_GROUP(safe_type);
TEST_SETUP(safe_type)
{
}
TEST_TEAR_DOWN(safe_type)
{
}

namespace sto = ehl::safe_type_operation;

TEST(safe_type, underlying_valye_can_be_read)
{
	using safe = ehl::safe_type<int, struct int_tag>;

	safe a{1};
	TEST_ASSERT_EQUAL_INT(1, a.get());

	safe b{2};
	TEST_ASSERT_EQUAL_INT(2, b.get());
}

TEST(safe_type, pre_increment_safe_types)
{
	using safe = ehl::safe_type<int, struct int_tag, sto::preincrement>;

	safe a{1};
	++a;

	TEST_ASSERT_EQUAL_INT(2, a.get());
}

TEST(safe_type, adding_safe_types)
{
	using safe = ehl::safe_type<int, struct int_tag, sto::add>;

	safe a{1};
	safe b{4};

	safe result = a + b;
	TEST_ASSERT_EQUAL_INT(5, result.get());
}

template<typename T>
using invalid_add_operation = decltype(ehl::declval<T&>() + ehl::declval<T&>() = ehl::declval<T&>());

TEST(safe_type, can_assign_to_lvalue_but_not_to_rvalue_of_safe_types)
{
	using safe = ehl::safe_type<int, struct int_tag, sto::add>;
	// This test passes if the code compiles

	safe a{0};
	safe b{1};

	a = b;

	TEST_ASSERT_EQUAL_INT(1, a.get());

	static_assert(!ehl::is_detected<invalid_add_operation, safe>::value, "'a + b = c' incorrectly allowed for safe_type");
}


TEST(safe_type, subtracting_safe_types)
{
	using safe = ehl::safe_type<int, struct int_tag, sto::subtract>;

	safe a{4};
	safe b{3};

	safe result = a - b;
	TEST_ASSERT_EQUAL_INT(1, result.get());
}

TEST(safe_type, comparing_safe_types)
{
	using safe = ehl::safe_type<int, struct int_tag, sto::compare>;

	safe one{1};
	safe oneOther{1};
	safe two{2};

	TEST_ASSERT_TRUE(one == oneOther);
	TEST_ASSERT_FALSE(one == two);

	TEST_ASSERT_TRUE(one != two);
	TEST_ASSERT_FALSE(one != oneOther);

	TEST_ASSERT_TRUE(one < two);
	TEST_ASSERT_FALSE(one < oneOther);

	TEST_ASSERT_TRUE(one <= oneOther);
	TEST_ASSERT_FALSE(two <= one);

	TEST_ASSERT_TRUE(two > one);
	TEST_ASSERT_FALSE(one > oneOther);

	TEST_ASSERT_TRUE(one >= oneOther);
	TEST_ASSERT_FALSE(one >= two);
}

TEST(safe_type, implicit_converting_safe_types)
{
	using safe_int = ehl::safe_type<int, struct int_tag>;

	using safe = ehl::safe_type<char, struct char_tag,
		sto::implicitly_convert_to<safe_int>::operation>;

	safe value{51};
	safe_int value_int = value;

	TEST_ASSERT_EQUAL_INT(51, value_int.get());
}

TEST(safe_type, adding_multiple_operations)
{
	using safe = ehl::safe_type<int, struct int_tag,
		sto::add,
		sto::subtract,
		sto::preincrement,
		sto::compare,
		sto::implicitly_convert_to<long>::operation
	>;

	safe a{0};
	(void)a;

	// This test passes if the code compiles
}

TEST(safe_type, operations_do_not_slice_extendable_objects)
{
	struct derived_safe : ehl::extendable_safe_type<int, derived_safe,
		sto::add>
	{
		using ehl::extendable_safe_type<int, derived_safe,
			sto::add>::extendable_safe_type;
	};

	derived_safe a{10};
	derived_safe b{10};

	derived_safe c = a + b;
	(void)c;

	// This test passes if the code compiles
}
