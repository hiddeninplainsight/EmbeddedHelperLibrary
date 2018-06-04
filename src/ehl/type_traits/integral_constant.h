#ifndef EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_INTEGRAL_CONSTANT_H
#define EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_INTEGRAL_CONSTANT_H

namespace ehl
{
	template <typename T, T v>
	struct integral_constant
	{
		static constexpr T value = v;

		constexpr operator T() const noexcept
		{
			return value;
		}

		constexpr T operator()() const noexcept
		{
			return value;
		}
	};

	template <bool b>
	struct bool_constant : integral_constant<bool, b>
	{
	};

	using true_type = bool_constant<true>;
	using false_type = bool_constant<false>;
}

#endif  // EMBEDDEDHELPERLIBRARY_TYPE_TRAITS_INTEGRAL_CONSTANT_H
