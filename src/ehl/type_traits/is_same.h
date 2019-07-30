#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_SAME_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_SAME_H

#include "integral_constant.h"

namespace ehl
{
	template <typename, typename>
	struct is_same : false_type
	{
	};

	template <typename T>
	struct is_same<T, T> : true_type
	{
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_SAME_H
