#ifndef EMBEDDEDHELPERLIBRARY_META_STRING_H
#define EMBEDDEDHELPERLIBRARY_META_STRING_H

#include "metaarray.h"

namespace ehl
{
	namespace meta
	{
		template <char... args>
		struct metastring : metaarray<char, args..., '\0'>
		{
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_META_STRING_H
