#ifndef EMBEDDEDHELPERLIBRARY_META_NUMBER_OF_DIGITS_H
#define EMBEDDEDHELPERLIBRARY_META_NUMBER_OF_DIGITS_H

namespace ehl
{
	namespace meta
	{
		namespace internal
		{
			template <unsigned int number, unsigned int v>
			struct number_of_digits
			{
				static const unsigned int value =
					1 + number_of_digits<number, v / 10>::value;
			};

			template <unsigned int number>
			struct number_of_digits<number, 0>
			{
				static unsigned int const value = number ? 0 : 1;
			};
		}

		template <unsigned int number>
		struct number_of_digits
		{
			static unsigned int const value =
				internal::number_of_digits<number, number>::value;
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_META_NUMBER_OF_DIGITS_H
