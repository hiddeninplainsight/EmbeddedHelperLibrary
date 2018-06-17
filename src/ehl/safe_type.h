#ifndef EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H
#define EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H

#include "compiler_help/empty_base_class_optimisation.h"
#include "crtp.h"

namespace ehl
{
	namespace detail
	{
		template <typename T>
		class safe_type_common
		{
		public:
			using raw_type = T;

		private:
			T value;

		public:
			explicit constexpr safe_type_common(T const& value)
				: value{value}
			{
			}

			T& raw_value()
			{
				return value;
			}

			constexpr T const& raw_value() const
			{
				return value;
			}
		};
	}

	template <typename T, typename Tag, template <typename> class... Operation>
	class EBCO safe_type
		: public detail::safe_type_common<T>
		, public Operation<safe_type<T, Tag, Operation...>>...
	{
		using detail::safe_type_common<T>::safe_type_common;
	public:
		using type = safe_type<T, Tag, Operation...>;

		// Allow construct from r-value and assign to l-value but do not
		// allow assign to r-value as it will make code that doesn't make sense
		// like `a + b = c` valid.
		safe_type(type&&) = default;
		type& operator=(type const&) & = default;
		type& operator=(type&&) & = default;

		type& operator=(type const&) && = delete;
		type& operator=(type&&) && = delete;
	};

	template <typename T, typename Derived, template <typename> class... Operation>
	class EBCO extendable_safe_type
		: public detail::safe_type_common<T>
		, public Operation<Derived>...
	{
		using detail::safe_type_common<T>::safe_type_common;
	};


	namespace safe_type_operation
	{
		template <typename T>
		struct add : crtp<T, add<T>>
		{
			T operator+(T const& right) const
			{
				return T(this->derived_object().raw_value() + right.raw_value());
			}
		};

		template <typename T>
		struct subtract : crtp<T, subtract<T>>
		{
			T operator-(T const& right) const
			{
				return T(this->derived_object().raw_value() - right.raw_value());
			}
		};

		template <typename T>
		struct preincrement : crtp<T, preincrement<T>>
		{
			T& operator++()
			{
				++this->derived_object().raw_value();
				return this->derived_object();
			}
		};

		template <typename T>
		struct equal : crtp<T, equal<T>>
		{
			bool operator==(T const& other) const
			{
				return this->derived_object().raw_value() == other.raw_value();
			}
		};

		template <typename T>
		struct not_equal : crtp<T, not_equal<T>>
		{
			bool operator!=(T const& other) const
			{
				return this->derived_object().raw_value() != other.raw_value();
			}
		};

		template <typename T>
		struct less_than : crtp<T, less_than<T>>
		{
			bool operator<(T const& other) const
			{
				return this->derived_object().raw_value() < other.raw_value();
			}
		};

		template <typename T>
		struct less_than_or_equal : crtp<T, less_than_or_equal<T>>
		{
			bool operator<=(T const& other) const
			{
				return this->derived_object().raw_value() <= other.raw_value();
			}
		};

		template <typename T>
		struct greater_than : crtp<T, greater_than<T>>
		{
			bool operator>(T const& other) const
			{
				return this->derived_object().raw_value() > other.raw_value();
			}
		};

		template <typename T>
		struct greater_than_or_equal : crtp<T, greater_than_or_equal<T>>
		{
			bool operator>=(T const& other) const
			{
				return this->derived_object().raw_value() >= other.raw_value();
			}
		};

		template <typename T>
		struct compare : equal<T>,
						 not_equal<T>,
						 less_than<T>,
						 less_than_or_equal<T>,
						 greater_than<T>,
						 greater_than_or_equal<T>
		{
		};

		template <typename U>
		struct implicitly_convert_to
		{
			template <typename T>
			struct operation : crtp<T, operation<T>>
			{
				operator U() const
				{
					return U{this->derived_object().raw_value()};
				}
			};
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H
