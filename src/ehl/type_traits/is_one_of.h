#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_ONE_OF_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_ONE_OF_H

#include "integral_constant.h"

namespace ehl
{
	template <typename T, typename... P0toN>
	struct is_one_of;

	// When no types are specified
	template <typename T>
	struct is_one_of<T> : false_type
	{
	};

	// Check if the head of the list matches
	template <typename T, typename... P1toN>
	struct is_one_of<T, T, P1toN...> : true_type
	{
	};

	// If the head of the list does not match parse the rest of the list
	template <typename T, typename P0, typename... P1toN>
	struct is_one_of<T, P0, P1toN...> : is_one_of<T, P1toN...>
	{
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_ONE_OF_H
