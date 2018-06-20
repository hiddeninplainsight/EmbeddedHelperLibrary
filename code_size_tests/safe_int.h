#ifndef EMBEDDEDHELPERLIBRARY_SAFE_INT_H
#define EMBEDDEDHELPERLIBRARY_SAFE_INT_H

#include "../src/ehl/safe_type.h"

using a_different_safe_int = ehl::safe_type<struct a_different_safe_int_tag,
											int, ehl::safe_type_limit::none>;

using safe_int =
	ehl::safe_type<struct safe_int_tag, int, ehl::safe_type_limit::none,
				   ehl::safe_type_operation::add,
				   ehl::safe_type_operation::implicitly_convert_to<
					   a_different_safe_int>::operation>;

#endif  // EMBEDDEDHELPERLIBRARY_SAFE_INT_H
