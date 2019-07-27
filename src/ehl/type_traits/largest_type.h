#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_LARGEST_TYPE_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_LARGEST_TYPE_H

namespace ehl
{
	template<typename T, typename... Tother>
	struct largest_type
	{
		static ::std::size_t constexpr size =
			sizeof(T) > largest_type<Tother...>::size ? sizeof(T)
													  : largest_type<Tother...>::size;
		static auto constexpr alignment =
			alignof(T) > largest_type<Tother...>::alignment ? alignof(T)
															: largest_type<Tother...>::alignment;

	};

	template<typename T>
	struct largest_type<T>
	{
		static ::std::size_t constexpr size = sizeof(T);
		static auto constexpr alignment = alignof(T);
	};
}

#endif //EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_LARGEST_TYPE_H
