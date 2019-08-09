#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_COMPILER_GENERATED_METHODS_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_COMPILER_GENERATED_METHODS_H

#include "declval.h"
#include "detection_idiom.h"
#include "void_t.h"

namespace ehl
{
	// Constructors
	template <class T>
	using default_construct_t = decltype(T());

	template <class T>
	using is_default_constructible = is_detected<default_construct_t, T>;

	template <class T>
	using copy_construct_t = decltype(T{declval<T const&>()});

	template <class T>
	using is_copy_constructible = is_detected<copy_construct_t, T>;

	template <class T>
	using move_construct_t = decltype(T{declval<T&&>()});

	template <class T>
	using is_move_constructible = is_detected<move_construct_t, T>;

	// Assignment
	template <class T>
	using copy_assign_t = decltype(declval<T&>() = declval<T const&>());

	template <class T>
	using is_copy_assignable = is_detected<copy_assign_t, T>;

	template <class T>
	using move_assign_t = decltype(declval<T&>() = declval<T&&>());

	template <class T>
	using is_move_assignable = is_detected<move_assign_t, T>;
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_COMPILER_GENERATED_METHODS_H
