#ifndef DETECTION_COMPILER_GENERATED_METHODS_TEST_TYPES_H
#define DETECTION_COMPILER_GENERATED_METHODS_TEST_TYPES_H

namespace compiler_generated_method_types
{
	struct everything_allowed
	{
	};

	struct no_default_construct
	{
		no_default_construct() = delete;
	};

	struct no_copy_construct
	{
		no_copy_construct(no_copy_construct const&) = delete;
		no_copy_construct(no_copy_construct&&) = default;
		no_copy_construct& operator=(no_copy_construct const&) = default;
		no_copy_construct& operator=(no_copy_construct&&) = default;
	};

	struct no_copy_assign
	{
		no_copy_assign(no_copy_assign const&) = default;
		no_copy_assign(no_copy_assign&&) = default;
		no_copy_assign& operator=(no_copy_assign const&) = delete;
		no_copy_assign& operator=(no_copy_assign&&) = default;
	};

	struct no_copy
	{
		no_copy(no_copy const&) = delete;
		no_copy(no_copy&&) = default;
		no_copy& operator=(no_copy const&) = delete;
		no_copy& operator=(no_copy&&) = default;
	};

	struct no_move_construct
	{
		no_move_construct(no_move_construct const&) = default;
		no_move_construct(no_move_construct&&) = delete;
		no_move_construct& operator=(no_move_construct const&) = default;
		no_move_construct& operator=(no_move_construct&&) = default;
	};

	struct no_move_assign
	{
		no_move_assign(no_move_assign const&) = default;
		no_move_assign(no_move_assign&&) = default;
		no_move_assign& operator=(no_move_assign const&) = default;
		no_move_assign& operator=(no_move_assign&&) = delete;
	};

	struct no_move
	{
		no_move(no_move const&) = default;
		no_move(no_move&&) = delete;
		no_move& operator=(no_move const&) = default;
		no_move& operator=(no_move&&) = delete;
	};
}  // namespace compiler_generated_method_types
#endif  // DETECTION_COMPILER_GENERATED_METHODS_TEST_TYPES_H
