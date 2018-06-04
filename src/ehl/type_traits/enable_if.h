#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_ENABLE_IF_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_ENABLE_IF_H

#include "type_is.h"

namespace ehl
{
	template <bool, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T> : type_is<T>
	{
	};

	template <bool B, class T = void>
	using enable_if_t = typename enable_if<B, T>::type;
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_ENABLE_IF_H
