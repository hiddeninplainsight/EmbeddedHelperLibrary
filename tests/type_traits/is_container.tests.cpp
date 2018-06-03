#include <ehl/type_traits/is_container.h>

using namespace ::ehl;

struct type_with_container_methods
{
	using reference = int;
	using iterator = short;
	using size_type = long;
	iterator begin();
	iterator end();
	reference operator[](size_type);
	size_type size();
};

struct type_with_no_functions
{
};

static_assert(is_container<type_with_container_methods>::value, "");
static_assert(!is_container<type_with_no_functions>::value, "");
