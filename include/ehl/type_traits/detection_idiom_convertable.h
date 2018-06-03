#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_IDIOM_CONVERTABLE_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_IDIOM_CONVERTABLE_H

#include <type_traits>
#include "detection_idiom.h"

namespace ehl
{
	template <class To, template <class...> class Op, class... Args>
	using is_detected_convertible =
		std::is_convertible<detected_t<Op, Args...>, To>;
}

#endif  // EMBEDDEDHELPERLIBRARY_DETECTION_IDIOM_CONVERTABLE_H
