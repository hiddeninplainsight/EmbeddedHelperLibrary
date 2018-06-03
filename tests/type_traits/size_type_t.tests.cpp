#include <ehl/type_traits/size_type_t.h>
#include <ehl/type_traits/detection_idiom.h>

using namespace ::ehl;

struct object_with_size_type
{
	using size_type = int;
};

struct object_with_no_size_type
{
};

static_assert(sizeof(detected_or<char, size_type_t, object_with_size_type>::type) == sizeof(object_with_size_type::size_type), "");
static_assert(sizeof(detected_or<char, size_type_t, object_with_no_size_type>::type) == sizeof(char), "");
