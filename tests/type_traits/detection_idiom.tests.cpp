#include <ehl/type_traits/detection_idiom.h>
#include <ehl/type_traits/declval.h>

using namespace ehl;

namespace
{
	struct type_with_int_f { int f(); };
	struct type_with_void_f { void f(); };
	struct type_with_no_f {};

	template<typename T>
	using f_t = decltype(declval<T>().f());
}
static_assert(is_detected<f_t, type_with_int_f>::value, "");
static_assert(is_detected<f_t, type_with_void_f>::value, "");
static_assert(!is_detected<f_t, type_with_no_f>::value, "");

static_assert(is_detected_exact<int, f_t, type_with_int_f>::value, "");
static_assert(!is_detected_exact<int, f_t, type_with_void_f>::value, "");
static_assert(!is_detected_exact<int, f_t, type_with_no_f>::value, "");

namespace
{
	struct type_with_type { using type = int; };
	struct type_with_no_type {};

	template<typename T>
	using type_member = typename T::type;
}
static_assert(sizeof(detected_or<char, type_member, type_with_type>::type) == sizeof(type_with_type::type), "");
static_assert(sizeof(detected_or<char, type_member, type_with_no_type>::type) == sizeof(char), "");
