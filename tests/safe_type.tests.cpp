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
namespace limit = ehl::safe_type_limit;

TEST(safe_type, underlying_value_can_be_read)
{
	using safe = ehl::safe_type<struct int_tag, int>;

	safe a{1};
	TEST_ASSERT_EQUAL_INT(1, a.raw_value());

	safe b{2};
	TEST_ASSERT_EQUAL_INT(2, b.raw_value());
}

TEST(safe_type, pre_increment_safe_types)
{
	using safe = ehl::safe_type<struct int_tag, int, sto::preincrement>;

	safe a{1};
	++a;

	TEST_ASSERT_EQUAL_INT(2, a.raw_value());
}

TEST(safe_type, adding_safe_types)
{
	using safe = ehl::safe_type<struct int_tag, int, sto::add>;

	safe a{1};
	safe b{4};

	safe result = a + b;
	TEST_ASSERT_EQUAL_INT(5, result.raw_value());
}

TEST(safe_type, can_copy_construct_an_lvalue)
{
	using safe = ehl::safe_type<struct int_tag, int, sto::add>;
	// This test passes if the code compiles

	safe a{34};
	safe b{a};

	TEST_ASSERT_EQUAL_INT(34, b.raw_value());
}

template<typename T>
using invalid_add_operation = decltype(ehl::declval<T&>() + ehl::declval<T&>() = ehl::declval<T&>());

TEST(safe_type, can_assign_to_lvalue_but_not_to_rvalue_of_safe_types)
{
	using safe = ehl::safe_type<struct int_tag, int, sto::add>;
	// This test passes if the code compiles

	safe a{0};
	safe b{1};

	a = b;

	TEST_ASSERT_EQUAL_INT(1, a.raw_value());

	static_assert(!ehl::is_detected<invalid_add_operation, safe>::value, "'a + b = c' incorrectly allowed for safe_type");
}


TEST(safe_type, subtracting_safe_types)
{
	using safe = ehl::safe_type<struct int_tag, int, sto::subtract>;

	safe a{4};
	safe b{3};

	safe result = a - b;
	TEST_ASSERT_EQUAL_INT(1, result.raw_value());
}

TEST(safe_type, comparing_safe_types)
{
	using safe = ehl::safe_type<struct int_tag, int, sto::compare>;

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
	using safe_int = ehl::safe_type<struct int_tag, int>;

	using safe = ehl::safe_type<struct char_tag, char,
		sto::implicitly_convert_to<safe_int>::operation>;

	safe value{51};
	safe_int value_int = value;

	TEST_ASSERT_EQUAL_INT(51, value_int.raw_value());
}

TEST(safe_type, adding_multiple_operations)
{
	using safe = ehl::safe_type<struct int_tag, int,
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
	struct derived_safe : ehl::extendable_safe_type<derived_safe, int,
		sto::add>
	{
		using ehl::extendable_safe_type<derived_safe, int,
			sto::add>::extendable_safe_type;
	};

	derived_safe a{10};
	derived_safe b{10};

	derived_safe c = a + b;
	(void)c;

	// This test passes if the code compiles
}

TEST(safe_type, range_limit_cannot_be_exceeded_for_safe_types)
{
	using safe = ehl::safe_type_limited<struct int_tag, int, limit::range<int, 2, 4>>;

	safe a{1};
	TEST_ASSERT_EQUAL_INT(2, a.raw_value());

	safe b{6};
	TEST_ASSERT_EQUAL_INT(4, b.raw_value());

	safe c{3};
	TEST_ASSERT_EQUAL_INT(3, c.raw_value());
}

TEST(safe_type, range_limit_cannot_be_exceeded_for_derived_safe_types)
{
	struct derived_safe : ehl::extendable_safe_type_limited<derived_safe, int, limit::range<int, 10, 20>>
	{
		using ehl::extendable_safe_type_limited<derived_safe, int, limit::range<int, 10, 20>>::extendable_safe_type_limited;
	};

	derived_safe a{1};
	TEST_ASSERT_EQUAL_INT(10, a.raw_value());

	derived_safe b{15};
	TEST_ASSERT_EQUAL_INT(15, b.raw_value());

	derived_safe c{100};
	TEST_ASSERT_EQUAL_INT(20, c.raw_value());
}

