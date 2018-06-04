#ifndef EMBEDDEDHELPERLIBRARY_SAFE_INT_H
#define EMBEDDEDHELPERLIBRARY_SAFE_INT_H

#include "../include/ehl/safe_type.h"

using a_different_safe_int = ehl::safe_type<int,
    struct a_different_safe_int_tag>;

using safe_int = ehl::safe_type<int, struct safe_int_tag,
	ehl::safe_type_operation::add,
	ehl::safe_type_operation::implicitly_convert_to<a_different_safe_int>::operation
>;

#endif //EMBEDDEDHELPERLIBRARY_SAFE_INT_H
