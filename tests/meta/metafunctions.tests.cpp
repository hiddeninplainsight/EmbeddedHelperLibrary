#include "ehl/meta/metastring.h"
#include "ehl/meta/number_of_digits.h"
#include "ehl/meta/number_to_string.h"

#include <unity_cpp.h>

TEST_GROUP(metafunctions);
TEST_SETUP(metafunctions)
{
}
TEST_TEAR_DOWN(metafunctions)
{
}

using namespace ::ehl::meta;

TEST(metafunctions, number_of_digits)
{
	unsigned int digits = number_of_digits<357>::value;
	TEST_ASSERT_EQUAL_UINT(3u, digits);

	digits = number_of_digits<0>::value;
	TEST_ASSERT_EQUAL_UINT(1u, digits);
}

TEST(metafunctions, metastring)
{
	static constexpr const char* five = metastring<'5'>::value;
	TEST_ASSERT_EQUAL_STRING("5", five);
}

TEST(metafunctions, number_to_string)
{
	static constexpr const char* five_nine_six = number_to_string<596>::value;
	TEST_ASSERT_EQUAL_STRING("596", five_nine_six);
}

