#ifndef EMBEDDEDHELPERLIBRARY_AS_RVALUE_H
#define EMBEDDEDHELPERLIBRARY_AS_RVALUE_H

#include "type_traits/remove_reference.h"

namespace ehl
{
	template<class T>
	typename remove_reference<T>::type&& as_rvalue(T &&t) noexcept
	{
		return static_cast<typename remove_reference<T>::type&&>(t);
	}
}

#endif //EMBEDDEDHELPERLIBRARY_AS_RVALUE_H
