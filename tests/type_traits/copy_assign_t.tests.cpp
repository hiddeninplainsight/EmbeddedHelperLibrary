#include <ehl/type_traits/copy_assign_t.h>
#include <ehl/type_traits/detection_idiom.h>

using namespace ehl;

struct type_with_copy_assign
{
	type_with_copy_assign& operator=(const type_with_copy_assign&)
	{
		return *this;
	}
};

struct type_with_odd_copy_assign
{
	void operator=(const type_with_odd_copy_assign &)
	{
	}
};

struct type_with_no_copy_assign
{
	type_with_no_copy_assign& operator=(const type_with_no_copy_assign&) = delete;
};

static_assert(is_detected_exact<type_with_copy_assign&, copy_assign_t, type_with_copy_assign>::value, "");
static_assert(!is_detected_exact<type_with_odd_copy_assign&, copy_assign_t, type_with_odd_copy_assign>::value, "");
static_assert(!is_detected_exact<type_with_no_copy_assign&, copy_assign_t, type_with_no_copy_assign>::value, "");
