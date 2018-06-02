#include <ehl/meta/literal_parser.h>
#include <unity_cpp.h>

TEST_GROUP(literal_parser);
TEST_SETUP(literal_parser)
{
}
TEST_TEAR_DOWN(literal_parser)
{
}

namespace
{
	template <char... chars>
	constexpr int operator""_number()
	{
		return ehl::meta::literal_parser<chars...>::value;
	}
}

TEST(literal_parser, Compile_time_checks)
{
	TEST_ASSERT_EQUAL_INT(10, 10_number);
}
