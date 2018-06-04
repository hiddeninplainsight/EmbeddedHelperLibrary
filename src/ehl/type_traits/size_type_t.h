#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_SIZE_T_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_SIZE_T_H

namespace ehl
{
	template <typename T>
	using size_type_t = typename T::size_type;
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_SIZE_T_H
