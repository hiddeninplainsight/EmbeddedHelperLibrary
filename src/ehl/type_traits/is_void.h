#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_VOID_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_VOID_H

#include "is_same.h"
#include "remove_cv.h"

namespace ehl
{
	template <typename T>
	using is_void = is_same<remove_cv_t<T>, void>;
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_VOID_H
