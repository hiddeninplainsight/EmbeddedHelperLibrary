#include <ehl/span.h>
#include <unity_cpp.h>
//#include <vector>

TEST_GROUP(span);
TEST_SETUP(span)
{
}
TEST_TEAR_DOWN(span)
{
}

template <typename T, typename iterator>
void EXPECT_SPAN_EQ(ehl::span<T>& dataSpan, iterator begin, iterator end)
{
	typename ehl::span<T>::iterator spanIterator = dataSpan.begin();

	for (iterator data = begin; data != end; ++data)
	{
		TEST_ASSERT_EQUAL_INT(*data, *spanIterator);
		++spanIterator;
	}

	TEST_ASSERT_EQUAL_PTR(spanIterator, dataSpan.end());
}

TEST(span, A_span_initialised_from_a_C_style_array_covers_the_entire_array)
{
	int data[] = {3, 5, 7, 9};

	ehl::span<int> dataSpan(data);

	EXPECT_SPAN_EQ(dataSpan, data, data + 4);
}

// TODO: Re-introduce container tests for span
/*TEST(span, A_span_initialised_from_a_CPP_style_array_covers_the_entire_array)
{
	std::array<int, 4> data = { 4, 6, 8, 10 };

	ehl::span<int> dataSpan{data};

	EXPECT_SPAN_EQ(dataSpan, data.begin(), data.end());
}*/
/*
TEST(span, A_span_initialised_from_a_std_vector_covers_the_entire_vector)
{
	std::vector<int> data;
	data.push_back(1);
	data.push_back(3);
	data.push_back(2);

	ehl::span<int> dataSpan(data);

	typedef std::vector<int>::iterator vectorIterator;

	EXPECT_SPAN_EQ<int, vectorIterator>(dataSpan, data.begin(), data.end());
}
*/
TEST(span, A_span_initialised_from_two_pointers)
{
	int data[] = {3, 5, 7, 9};

	ehl::span<int> dataSpan(data + 1, data + 3);

	ehl::span<int>::iterator spanIterator = dataSpan.begin();

	TEST_ASSERT_EQUAL_INT(data[1], *spanIterator);
	++spanIterator;

	TEST_ASSERT_EQUAL_INT(data[2], *spanIterator);
	++spanIterator;

	TEST_ASSERT_EQUAL_PTR(spanIterator, dataSpan.end());
}

TEST(span, A_span_can_be_copied)
{
	int data[] = {3, 5, 7, 9};

	ehl::span<int> originalSpan(data);
	ehl::span<int> copiedSpan(originalSpan);

	EXPECT_SPAN_EQ<int, int*>(copiedSpan, data, data + 4);
}

TEST(span, A_span_can_be_copied_to_a_const_version_of_itself)
{
	int data[] = {3, 5, 7, 9};

	ehl::span<int> originalSpan(data);
	ehl::span<const int> copiedSpan(originalSpan);

	EXPECT_SPAN_EQ<int const, int const*>(copiedSpan, data, data + 4);
}

TEST(span, An_already_initialised_span_can_have_another_one_copied_over_it)
{
	int data[] = {3, 5, 7, 9};
	int data2[] = {1};

	ehl::span<int> originalSpan(data);
	ehl::span<int> copiedSpan(data2);

	copiedSpan = originalSpan;

	EXPECT_SPAN_EQ<int, int*>(copiedSpan, data, data + 4);
}
