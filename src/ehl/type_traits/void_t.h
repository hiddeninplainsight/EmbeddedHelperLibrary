#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_VOID_T_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_VOID_T_H

namespace ehl
{
#ifdef EHL_CWG_1558_WORKAROUND
	template <typename...>
	struct voider
	{
		using type = void;
	};

	template <typename... T0toN>
	using void_t = typename voider<T0toN...>::type;
#else
	template <typename...>
	using void_t = void;
#endif
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_VOID_T_H
