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
			*d_first++ = unary_op(*first1++);
		}
		return d_first;
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_ALGORITHM_H
