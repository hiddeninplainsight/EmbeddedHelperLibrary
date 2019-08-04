#include <ehl/optional.h>

#include <ehl/rvalue.h>
#include <unity_cpp.h>

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

namespace
{
	class RecordOperations
	{
	public:
		bool defaultConstructed{false};
		bool copyConstructed{false};
		bool moveConstructed{false};
		static int globalCopyConstructCount;
		static int globalCopyAssignCount;
		static int globalMoveConstructCount;
		static int globalMoveAssignCount;
		bool copyAssigned{false};
		bool moveAssigned{false};
		bool* destructed{nullptr};

		RecordOperations()
			: defaultConstructed{true}
		{
		}

		explicit RecordOperations(bool* destructed)
			: destructed{destructed}
		{
		}

		RecordOperations(RecordOperations const& other)
			: copyConstructed{true}
			, destructed{other.destructed}
		{
			++globalCopyConstructCount;
		}

		RecordOperations(RecordOperations&& other)
			: moveConstructed{true}
			, destructed{other.destructed}
		{
			++globalMoveConstructCount;
		}

		RecordOperations& operator=(RecordOperations const&)
		{
			++globalCopyAssignCount;
			copyAssigned = true;
			return *this;
		}

		RecordOperations& operator=(RecordOperations&&)
		{
			++globalMoveAssignCount;
			moveAssigned = true;
			return *this;
		}

		~RecordOperations()
		{
			if (destructed)
				*destructed = true;
		}

		static void ClearCounters()
		{
			globalCopyConstructCount = 0;
			globalCopyAssignCount = 0;
			globalMoveConstructCount = 0;
			globalMoveAssignCount = 0;
		}
	};

	int RecordOperations::globalCopyConstructCount{0};
	int RecordOperations::globalCopyAssignCount{0};
	int RecordOperations::globalMoveConstructCount{0};
	int RecordOperations::globalMoveAssignCount{0};
}

TEST(optional, Assigning_an_lvalue_object_to_an_optional_that_does_not_conatin_a_value_copy_constructs_the_value_into_the_optional)
{
	RecordOperations object;

	ehl::optional<RecordOperations> anOptional;
	anOptional = object;

	TEST_ASSERT_TRUE(anOptional.value().copyConstructed);
}

TEST(optional, If_an_optional_contains_a_value_it_is_destroyed_when_the_optional_is_destroyed)
{
	bool objectDestructed{false};
	RecordOperations object{&objectDestructed};

	{
		ehl::optional<RecordOperations> anOptional;
		anOptional = object;
		TEST_ASSERT_FALSE(objectDestructed);
	}

	TEST_ASSERT_TRUE(objectDestructed);
}

TEST(optional, Assigning_an_lvalue_object_to_an_optional_that_conatins_a_value_copy_assigns_the_value_into_the_optional)
{
	RecordOperations object1;
	RecordOperations object2;

	ehl::optional<RecordOperations> anOptional;
	anOptional = object1;
	TEST_ASSERT_FALSE(anOptional.value().copyAssigned);

	anOptional = object2;

	TEST_ASSERT_TRUE(anOptional.value().copyAssigned);
}

TEST(optional, Copying_an_optional_with_an_value_set_into_a_uninitialised_optional_copy_constructs_the_value_into_the_new_optional)
{
	RecordOperations object;

	ehl::optional<RecordOperations> optional1;
	optional1 = object;
	// The value will be copy constructed by the previous assignment, clear
	// this as a default copy constructor will memory copy the valueData array
	// which will set the copyConstructed flag in the copied object even though
	// it hasn't been copy constructed
	optional1.value().copyConstructed = false;

	ehl::optional<RecordOperations> optional2{optional1};

	TEST_ASSERT_TRUE(optional2.is_valid());
	TEST_ASSERT_TRUE(optional2.value().copyConstructed);
}

TEST(optional, Copy_constructing_an_optional_that_does_not_contain_a_value_does_not_copy_construct_the_value_into_the_new_optional)
{
	RecordOperations object;

	ehl::optional<RecordOperations> optional1;

	RecordOperations::globalCopyConstructCount = 0;

	ehl::optional<RecordOperations> optional2{optional1};

	TEST_ASSERT_FALSE(optional2.is_valid());
	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyConstructCount);
}

TEST(optional, Copy_constructing_an_optional_with_a_value)
{
	RecordOperations object;

	ehl::optional<RecordOperations> anOptional{object};

	TEST_ASSERT_TRUE(anOptional.is_valid());
	TEST_ASSERT_TRUE(anOptional.value().copyConstructed);
}

TEST(optional, Move_constructing_an_optional_with_a_value)
{
	ehl::optional<RecordOperations> anOptional{RecordOperations{}};

	TEST_ASSERT_TRUE(anOptional.is_valid());
	TEST_ASSERT_FALSE(anOptional.value().copyConstructed);
	TEST_ASSERT_TRUE(anOptional.value().moveConstructed);
}

TEST(optional, Move_constructing_an_optional_with_an_optional_with_a_value_set)
{
	RecordOperations object;
	ehl::optional<RecordOperations> anOptionalWithAValue{object};

	ehl::optional<RecordOperations> anOptional{ehl::as_rvalue(anOptionalWithAValue)};

	TEST_ASSERT_TRUE(anOptional.is_valid());
	TEST_ASSERT_TRUE(anOptional.value().moveConstructed);
}

TEST(optional, Move_constructing_an_optional_with_an_optional_with_no_value_set)
{
	ehl::optional<RecordOperations> anOptionalWithNoValue;

	RecordOperations::globalMoveConstructCount = 0;
	ehl::optional<RecordOperations> anOptional{ehl::as_rvalue(anOptionalWithNoValue)};

	TEST_ASSERT_FALSE(anOptional.is_valid());
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveConstructCount);
}

TEST(optional, Move_assigning_an_optional_with_no_value_set_with_an_optional_with_no_value_set)
{
	ehl::optional<RecordOperations> anOptionalWithNoValue;
	ehl::optional<RecordOperations> anOptional;

	RecordOperations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithNoValue);

	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveConstructCount);
	TEST_ASSERT_FALSE(anOptional.is_valid());
}

TEST(optional, Move_assigning_an_optional_with_no_value_set_with_an_optional_with_a_value_set)
{
	RecordOperations value;
	ehl::optional<RecordOperations> anOptionalWithAValue{value};
	ehl::optional<RecordOperations> anOptional;

	RecordOperations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithAValue);

	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(1, RecordOperations::globalMoveConstructCount);
	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, Move_assigning_an_optional_with_a_value_set_with_an_optional_with_a_value_set)
{
	RecordOperations value;
	ehl::optional<RecordOperations> anOptionalWithAValue{value};
	RecordOperations value2;
	ehl::optional<RecordOperations> anOptional{value2};

	RecordOperations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithAValue);

	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(1, RecordOperations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveConstructCount);
	TEST_ASSERT_TRUE(anOptional.is_valid());
}

TEST(optional, Move_assigning_an_optional_with_a_value_set_with_an_optional_with_no_value_set)
{
	ehl::optional<RecordOperations> anOptionalWithNoValue;
	bool valueDestroyed{false};
	RecordOperations value{&valueDestroyed};
	ehl::optional<RecordOperations> anOptional{value};

	RecordOperations::ClearCounters();
	anOptional = ehl::as_rvalue(anOptionalWithNoValue);

	TEST_ASSERT_TRUE(valueDestroyed);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalCopyConstructCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveAssignCount);
	TEST_ASSERT_EQUAL(0, RecordOperations::globalMoveConstructCount);
	TEST_ASSERT_FALSE(anOptional.is_valid());
}
