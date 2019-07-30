#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_HAS_TYPE_MEMBER_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_HAS_TYPE_MEMBER_H

#include "integral_constant.h"
#include "void_t.h"

namespace ehl
{
	template <typename, typename = void>
	struct has_type_member : false_type
	{
	};

	template <typename T>
	struct has_type_member<T, void_t<typename T::type>> : true_type
	{
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_HAS_TYPE_MEMBER_H
