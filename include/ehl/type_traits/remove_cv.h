#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_REMOVE_CV_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_REMOVE_CV_H

#include "type_is.h"

namespace ehl
{
	template <typename T>
	struct remove_const : type_is<T>
	{
	};

	template <typename T>
	struct remove_const<T const> : type_is<T>
	{
	};

	template <typename T>
	using remove_const_t = typename remove_const<T>::type;

	template <typename T>
	struct remove_volatile : type_is<T>
	{
	};

	template <typename T>
	struct remove_volatile<T volatile> : type_is<T>
	{
	};

	template <typename T>
	using remove_volatile_t = typename remove_volatile<T>::type;

	template <typename T>
	using remove_cv = remove_volatile<remove_const_t<T>>;

	template <typename T>
	using remove_cv_t = typename remove_cv<T>::type;
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_REMOVE_CV_H
