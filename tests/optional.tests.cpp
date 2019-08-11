#include <ehl/optional.h>

#include <ehl/rvalue.h>
#include <unity_cpp.h>

#include "recorded_operations.h"
#include "type_traits/detection_compiler_generated_methods.test_types.h"
#include <ehl/type_traits/detection_compiler_generated_methods.h>

TEST_GROUP(optional);
TEST_SETUP(optional)
{
}
TEST_TEAR_DOWN(optional)
{
}

TEST(optional, Default_constructed_obejct_is_invalid)
{
	ehl::optional<int> anOptional;

	TEST_ASSERT_FALSE(anOptional.is_valid());
}

TEST(optional, Assigning_to_an_optionl_makes_it_valid)
{
	ehl::optional<int> anOptional;

	anOptional = 2;

	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, The_value_an_optional_was_set_to_can_be_read_back)
{
	ehl::optional<int> anOptional;

	anOptional = 2;

	TEST_ASSERT_EQUAL(2, anOptional.value());
}

TEST(optional, Assigning_an_lvalue_object_to_an_optional_that_does_not_conatin_a_value_copy_constructs_the_value_into_the_optional)
{
	record_operations object;

	ehl::optional<record_operations> anOptional;
	anOptional = object;

	TEST_ASSERT_TRUE(anOptional.value().copyConstructed);
}

TEST(optional, If_an_optional_contains_a_value_it_is_destroyed_when_the_optional_is_destroyed)
{
	bool objectDestructed{false};
	record_operations object{&objectDestructed};

	{
		ehl::optional<record_operations> anOptional;
		anOptional = object;
		TEST_ASSERT_FALSE(objectDestructed);
	}

	TEST_ASSERT_TRUE(objectDestructed);
}

TEST(optional, Assigning_an_lvalue_object_to_an_optional_that_conatins_a_value_copy_assigns_the_value_into_the_optional)
{
	record_operations object1;
	record_operations object2;

	ehl::optional<record_operations> anOptional;
	anOptional = object1;
	TEST_ASSERT_FALSE(anOptional.value().copyAssigned);

	anOptional = object2;

	TEST_ASSERT_TRUE(anOptional.value().copyAssigned);
}

TEST(optional, Copying_an_optional_with_an_value_set_into_a_uninitialised_optional_copy_constructs_the_value_into_the_new_optional)
{
	record_operations object;

	ehl::optional<record_operations> optional1;
	optional1 = object;
	// The value will be copy constructed by the previous assignment, clear
	// this as a default copy constructor will memory copy the valueData array
	// which will set the copyConstructed flag in the copied object even though
	// it hasn't been copy constructed
	optional1.value().copyConstructed = false;

	ehl::optional<record_operations> optional2{optional1};

	TEST_ASSERT_TRUE(optional2.is_valid());
	TEST_ASSERT_TRUE(optional2.value().copyConstructed);
}

TEST(optional, Copy_constructing_an_optional_that_does_not_contain_a_value_does_not_copy_construct_the_value_into_the_new_optional)
{
	record_operations object;

	ehl::optional<record_operations> optional1;

	record_operations::globalCopyConstructCount = 0;

	ehl::optional<record_operations> optional2{optional1};

	TEST_ASSERT_FALSE(optional2.is_valid());
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
}

TEST(optional, Copy_constructing_an_optional_with_a_value)
{
	record_operations object;

	ehl::optional<record_operations> anOptional{object};

	TEST_ASSERT_TRUE(anOptional.is_valid());
	TEST_ASSERT_TRUE(anOptional.value().copyConstructed);
}

TEST(optional, Move_constructing_an_optional_with_a_value)
{
	ehl::optional<record_operations> anOptional{record_operations{}};

	TEST_ASSERT_TRUE(anOptional.is_valid());
	TEST_ASSERT_FALSE(anOptional.value().copyConstructed);
	TEST_ASSERT_TRUE(anOptional.value().moveConstructed);
}

TEST(optional, Move_constructing_an_optional_with_an_optional_with_a_value_set)
{
	record_operations object;
	ehl::optional<record_operations> anOptionalWithAValue{object};

	ehl::optional<record_operations> anOptional{ehl::as_rvalue(anOptionalWithAValue)};

	TEST_ASSERT_TRUE(anOptional.is_valid());
	TEST_ASSERT_TRUE(anOptional.value().moveConstructed);
}

TEST(optional, Move_constructing_an_optional_with_an_optional_with_no_value_set)
{
	ehl::optional<record_operations> anOptionalWithNoValue;

	record_operations::globalMoveConstructCount = 0;
	ehl::optional<record_operations> anOptional{ehl::as_rvalue(anOptionalWithNoValue)};

	TEST_ASSERT_FALSE(anOptional.is_valid());
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
}

TEST(optional, Move_assigning_an_optional_with_no_value_set_with_an_optional_with_no_value_set)
{
	ehl::optional<record_operations> anOptionalWithNoValue;
	ehl::optional<record_operations> anOptional;

	record_operations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithNoValue);

	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_FALSE(anOptional.is_valid());
}

TEST(optional, Move_assigning_an_optional_with_no_value_set_with_an_optional_with_a_value_set)
{
	record_operations value;
	ehl::optional<record_operations> anOptionalWithAValue{value};
	ehl::optional<record_operations> anOptional;

	record_operations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithAValue);

	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(1, record_operations::globalMoveConstructCount);
	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, Move_assigning_an_optional_with_a_value_set_with_an_optional_with_a_value_set)
{
	record_operations value;
	ehl::optional<record_operations> anOptionalWithAValue{value};
	record_operations value2;
	ehl::optional<record_operations> anOptional{value2};

	record_operations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithAValue);

	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(1, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, Move_assigning_an_optional_with_a_value_set_with_an_optional_with_no_value_set)
{
	ehl::optional<record_operations> anOptionalWithNoValue;
	bool valueDestroyed{false};
	record_operations value{&valueDestroyed};
	ehl::optional<record_operations> anOptional{value};

	record_operations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithNoValue);

	TEST_ASSERT_TRUE(valueDestroyed);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_FALSE(anOptional.is_valid());
}

TEST(optional, Copy_assigning_an_optional_with_no_value_set_with_an_optional_with_no_value_set)
{
	ehl::optional<record_operations> anOptionalWithNoValue;
	ehl::optional<record_operations> anOptional;

	record_operations::ClearCounters();
	anOptional = anOptionalWithNoValue;

	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_FALSE(anOptional.is_valid());
}

TEST(optional, Copy_assigning_an_optional_with_no_value_set_with_an_optional_with_a_value_set)
{
	record_operations value;
	ehl::optional<record_operations> anOptionalWithAValue{value};
	ehl::optional<record_operations> anOptional;

	record_operations::ClearCounters();
	anOptional = anOptionalWithAValue;

	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(1, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, Copy_assigning_an_optional_with_a_value_set_with_an_optional_with_a_value_set)
{
	record_operations value;
	ehl::optional<record_operations> anOptionalWithAValue{value};
	record_operations value2;
	ehl::optional<record_operations> anOptional{value2};

	record_operations::ClearCounters();
	anOptional = anOptionalWithAValue;

	TEST_ASSERT_EQUAL(1, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, Copy_assigning_an_optional_with_a_value_set_with_an_optional_with_no_value_set)
{
	ehl::optional<record_operations> anOptionalWithNoValue;
	bool valueDestroyed{false};
	record_operations value{&valueDestroyed};
	ehl::optional<record_operations> anOptional{value};

	record_operations::ClearCounters();
	anOptional = anOptionalWithNoValue;

	TEST_ASSERT_TRUE(valueDestroyed);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, record_operations::globalMoveConstructCount);
	TEST_ASSERT_FALSE(anOptional.is_valid());
}

using namespace ::compiler_generated_method_types;

static_assert(ehl::is_copy_constructible<record_operations>::value, "");
static_assert(ehl::is_copy_assignable<record_operations>::value, "");

using optional_all_allowed = ::ehl::optional<everything_allowed>;
using optional_no_copy_construct = ehl::optional<no_copy_construct>;
using optional_no_copy_assign = ehl::optional<no_copy_assign>;
using optional_no_copy = ehl::optional<no_copy>;
using optional_no_move_construct = ehl::optional<no_move_construct>;
using optional_no_move_assign = ehl::optional<no_move_assign>;
using optional_no_move = ehl::optional<no_move>;

template<typename T, bool copyConstruct, bool copyAssign, bool moveConstruct, bool moveAssign>
struct HasConstructAssign
{
	static_assert(::ehl::is_copy_constructible<T>::value == copyConstruct, "");
	static_assert(::ehl::is_copy_assignable<T>::value == copyAssign, "");
	static_assert(::ehl::is_move_constructible<T>::value == moveConstruct, "");
	static_assert(::ehl::is_move_assignable<T>::value == moveAssign, "");
};

HasConstructAssign<optional_all_allowed, true, true, true, true> testOptionalAll;
HasConstructAssign<optional_no_copy_construct, false, false, true, true> testOptionalNoCopyConstruct;
HasConstructAssign<optional_no_copy_assign, false, false, true, true> testOptionalNoCopyAssign;
HasConstructAssign<optional_no_copy, false, false, true, true> testOptionalNoCopy;
HasConstructAssign<optional_no_move_construct, true, true, false, false> testOptionalNoMoveConstruct;
HasConstructAssign<optional_no_move_assign, true, true, false, false> testOptionalNoMoveAssign;
HasConstructAssign<optional_no_move, true, true, false, false> testOptionalNoMove;

template<typename... From>
struct is_constructable_from_t
{
	template<typename T>
	using operation_t = decltype(T(::ehl::declval<From>()...));
};

template <class T, typename... From>
using is_constructable_from = ::ehl::is_detected<is_constructable_from_t<From...>:: template operation_t, T>;

static_assert(is_constructable_from<optional_all_allowed, everything_allowed const&>::value, "");
static_assert(is_constructable_from<optional_all_allowed, everything_allowed&&>::value, "");

static_assert(is_constructable_from<optional_no_copy, no_copy const&>::value == false, "");
static_assert(is_constructable_from<optional_no_copy, no_copy&&>::value, "");

static_assert(is_constructable_from<optional_no_move, no_move const&>::value, "");
//static_assert(is_constructable_from<optional_no_move, no_move&&>::value == false, "");
