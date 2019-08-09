#include "detection_compiler_generated_methods.test_types.h"

#include <ehl/type_traits/detection_compiler_generated_methods.h>

using namespace ::ehl;
using namespace ::compiler_generated_method_types;

// is_default_constructible
static_assert(is_default_constructible<everything_allowed>::value, "");
static_assert(is_default_constructible<no_default_construct>::value == false, "");

// is_copy_constructible
static_assert(is_copy_constructible<everything_allowed>::value, "");
static_assert(is_copy_constructible<no_copy_construct>::value == false, "");
static_assert(is_copy_constructible<no_copy_assign>::value, "");
static_assert(is_copy_constructible<no_move_construct>::value, "");
static_assert(is_copy_constructible<no_move_assign>::value, "");
static_assert(is_copy_constructible<no_move>::value, "");

// is_move_constructible
static_assert(is_move_constructible<everything_allowed>::value, "");
static_assert(is_move_constructible<no_copy_construct>::value, "");
static_assert(is_move_constructible<no_copy_assign>::value, "");
static_assert(is_move_constructible<no_move_construct>::value == false, "");
static_assert(is_move_constructible<no_move_assign>::value, "");
static_assert(is_move_constructible<no_move>::value == false, "");

// is_copy_assignable
static_assert(is_copy_assignable<everything_allowed>::value, "");
static_assert(is_copy_assignable<no_copy_construct>::value, "");
static_assert(is_copy_assignable<no_copy_assign>::value == false, "");
static_assert(is_copy_assignable<no_move_construct>::value, "");
static_assert(is_copy_assignable<no_move_assign>::value, "");
static_assert(is_copy_assignable<no_move>::value, "");

// is_move_assignable
static_assert(is_move_assignable<everything_allowed>::value, "");
static_assert(is_move_assignable<no_copy_construct>::value, "");
static_assert(is_move_assignable<no_copy_assign>::value, "");
static_assert(is_move_assignable<no_move_construct>::value, "");
static_assert(is_move_assignable<no_move_assign>::value == false, "");
static_assert(is_move_assignable<no_move>::value == false, "");
