#ifndef EMBEDDEDHELPERLIBRARY_META_ARRAY_H
#define EMBEDDEDHELPERLIBRARY_META_ARRAY_H

namespace ehl
{
	namespace meta
	{
		template <typename T, T... args>
		struct metaarray
		{
			using type = T[sizeof...(args)];

			static constexpr type value = {args...};
		};

		template <typename T, T... args>
		constexpr
			typename metaarray<T, args...>::type metaarray<T, args...>::value;
	}  // namespace meta
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_META_ARRAY_H
