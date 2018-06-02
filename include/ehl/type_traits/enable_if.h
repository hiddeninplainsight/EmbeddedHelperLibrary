#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_ENABLE_IF_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_ENABLE_IF_H

namespace ehl
{
	namespace type_traits
	{
		template <bool B, class T = void>
		struct enable_if
		{
		};

		template <class T>
		struct enable_if<true, T>
		{
			typedef T type;
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_ENABLE_IF_H
