#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_RANK_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_RANK_H

#include "integral_constant.h"

namespace ehl
{
	template <typename T>
	struct rank : integral_constant<size_t, 0u>
	{
	};

	template <typename T, size_t N>
	struct rank<T[N]> : integral_constant<size_t, 1u + rank<T>::value>
	{
	};

	template <typename T>
	struct rank<T[]> : integral_constant<size_t, 1u + rank<T>::value>
	{
	};
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_RANK_H
