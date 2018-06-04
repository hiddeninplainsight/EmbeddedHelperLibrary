#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_TYPE_IS_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_TYPE_IS_H

namespace ehl
{
	template <typename T>
	struct type_is
	{
		using type = T;
	};
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_TYPE_IS_H
