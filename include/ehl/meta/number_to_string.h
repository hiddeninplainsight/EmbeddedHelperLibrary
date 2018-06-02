#ifndef EMBEDDEDHELPERLIBRARY_META_NUMBER_TO_STRING_H
#define EMBEDDEDHELPERLIBRARY_META_NUMBER_TO_STRING_H

#include "metastring.h"
#include "number_of_digits.h"

namespace ehl
{
	namespace meta
	{
		namespace internal
		{
			template <unsigned int digits, unsigned int number, char... args>
			struct number_to_string
			{
				static constexpr char const* const value =
					number_to_string<digits - 1, number / 10,
									 ('0' + (number % 10)), args...>::value;
			};

			template <char... args>
			struct number_to_string<0, 0, args...>
			{
				static constexpr char const* const value =
					metastring<args...>::value;
			};
		}

		template <unsigned int number>
		struct number_to_string
		{
			static constexpr char const* const value =
				internal::number_to_string<number_of_digits<number>::value,
										   number>::value;
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_META_NUMBER_TO_STRING_H
