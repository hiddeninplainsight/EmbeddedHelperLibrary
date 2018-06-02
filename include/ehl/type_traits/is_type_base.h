#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_TYPE_BASE_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_TYPE_BASE_H

namespace ehl
{
	namespace type_traits
	{
		struct is_type_base
		{
			typedef char yes[1];
			typedef yes no[2];

			template <typename U, U u>
			struct FunctionSignatureMatches;
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_TYPE_BASE_H
