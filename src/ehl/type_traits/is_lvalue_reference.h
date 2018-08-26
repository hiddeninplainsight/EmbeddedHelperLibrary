#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_LVALUE_REFERENCE_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_LVALUE_REFERENCE_H

#include "integral_constant.h"

namespace ehl
{
	template<typename T>
	struct is_lvalue_reference : public false_type
	{
	};

	template<typename T>
	struct is_lvalue_reference<T&> : public true_type
	{
	};

}

#endif //EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_LVALUE_REFERENCE_H
