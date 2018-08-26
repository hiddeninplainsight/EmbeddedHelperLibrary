#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_REMOVE_REFERENCE_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_REMOVE_REFERENCE_H

namespace ehl
{
	template<typename T>
	struct remove_reference
	{
		using type = T;
	};

	template<typename T>
	struct remove_reference<T &>
	{
		using type = T;
	};

	template<typename T>
	struct remove_reference<T &&>
	{
		using type = T;
	};
}

#endif //EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_REMOVE_REFERENCE_H
