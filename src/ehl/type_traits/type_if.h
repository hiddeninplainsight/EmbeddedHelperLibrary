#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_TYPE_IF_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_TYPE_IF_H

#include "type_is.h"

namespace ehl
{
	template <bool, typename T, typename>
	struct type_if : type_is<T>
	{
	};

	template <typename T, typename F>
	struct type_if<false, T, F> : type_is<F>
	{
	};

	template <bool p, typename T, typename F>
	using type_if_t = typename type_if<p, T, F>::type;
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_IF_H
