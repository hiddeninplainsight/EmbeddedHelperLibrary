#ifndef EMBEDDEDHELPERLIBRARY_AS_RVALUE_H
#define EMBEDDEDHELPERLIBRARY_AS_RVALUE_H

#include "type_traits/is_lvalue_reference.h"
#include "type_traits/remove_reference.h"

namespace ehl
{
	template <class T>
	typename remove_reference<T>::type&& as_rvalue(T&& t) noexcept
	{
		return static_cast<typename remove_reference<T>::type&&>(t);
	}

	template <typename T>
	constexpr T&& forward(typename remove_reference<T>::type& t) noexcept
	{
		return static_cast<T&&>(t);
	}

	template <typename T>
	constexpr T&& forward(typename remove_reference<T>::type&& t) noexcept
	{
		static_assert(
			!is_lvalue_reference<T>::value,
			"template argument substituting T is an lvalue reference type");
		return static_cast<T&&>(t);
	}
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_AS_RVALUE_H
