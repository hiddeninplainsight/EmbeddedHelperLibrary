#ifndef EMBEDDEDHELPERLIBRARY_ALGORITHM_H
#define EMBEDDEDHELPERLIBRARY_ALGORITHM_H

namespace ehl
{
	template <class InputIt, class OutputIt, class UnaryOperation>
	OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first,
					   UnaryOperation unary_op)
	{
		while (first1 != last1)
		{
			*d_first = unary_op(*first1);
			d_first++;
			first1++;
		}
		return d_first;
	}

	template <class InputIt, class UnaryPredicate>
	InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++first)
		{
			if (p(*first))
			{
				return first;
			}
		}
		return last;
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_ALGORITHM_H
