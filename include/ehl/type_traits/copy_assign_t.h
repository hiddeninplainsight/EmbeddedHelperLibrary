#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_COPY_ASSIGN_T_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_COPY_ASSIGN_T_H

#include <utility>

namespace ehl
{
	template <class T>
	using copy_assign_t =
		decltype(std::declval<T&>() = std::declval<T const&>());
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_COPY_ASSIGN_T_H
