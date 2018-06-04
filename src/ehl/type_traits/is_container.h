#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_CONTAINER_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_CONTAINER_H

#include "declval.h"
#include "enable_if.h"
#include "integral_constant.h"
#include "is_same.h"
#include "size_type_t.h"
#include "void_t.h"

namespace ehl
{
	template <typename T>
	using container_iterator_t = typename T::iterator;

	template <typename T>
	using container_reference_t = typename T::reference;

	template <typename T>
	using container_begin_method_t = decltype(declval<T>().begin());

	template <typename T>
	using container_end_method_t = decltype(declval<T>().end());

	// Braces around the `declval<container_size_t<T>>()` parameter to check the
	// parameter
	// type is correct
	template <typename T>
	using container_element_access_t =
		decltype(declval<T>()[{declval<size_type_t<T>>()}]);

	template <typename T>
	using container_size_method_t = decltype(declval<T>().size());

	template <typename T, typename = void>
	struct is_container : false_type
	{
	};

	template <typename T>
	struct is_container<
		T, void_t<enable_if_t<is_same<container_iterator_t<T>,
									  container_begin_method_t<T>>::value>,
				  enable_if_t<is_same<container_iterator_t<T>,
									  container_end_method_t<T>>::value>,
				  enable_if_t<is_same<container_reference_t<T>,
									  container_element_access_t<T>>::value>,
				  enable_if_t<is_same<size_type_t<T>,
									  container_size_method_t<T>>::value>>>
		: true_type
	{
	};
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_IS_CONTAINER_H
