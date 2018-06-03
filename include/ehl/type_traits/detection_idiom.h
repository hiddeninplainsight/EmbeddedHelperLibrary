#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_IDIOM_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_IDIOM_H

#include "integral_constant.h"
#include "is_same.h"
#include "void_t.h"

namespace ehl
{
	struct nonesuch
	{
		nonesuch() = delete;
		~nonesuch() = delete;
		nonesuch(nonesuch const&) = delete;
		void operator=(nonesuch const&) = delete;
	};

	namespace detail
	{
		template <class Default, class AlwaysVoid, template <class...> class Op,
				  class... Args>
		struct detector
		{
			using value_t = false_type;
			using type = Default;
		};

		template <class Default, template <class...> class Op, class... Args>
		struct detector<Default, void_t<Op<Args...>>, Op, Args...>
		{
			using value_t = true_type;
			using type = Op<Args...>;
		};
	}

	template <template <class...> class Op, class... Args>
	using is_detected =
		typename detail::detector<nonesuch, void, Op, Args...>::value_t;

	template <template <class...> class Op, class... Args>
	using detected_t =
		typename detail::detector<nonesuch, void, Op, Args...>::type;

	template <class Default, template <class...> class Op, class... Args>
	using detected_or = detail::detector<Default, void, Op, Args...>;

	template <class Expected, template <class...> class Op, class... Args>
	using is_detected_exact = is_same<Expected, detected_t<Op, Args...>>;
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_DETECTION_IDIOM_H
