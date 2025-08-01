#ifndef EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H
#define EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H

#include "compiler_help/empty_base_class_optimisation.h"
#include "crtp.h"

namespace ehl
{
	namespace detail
	{
		template <typename T, typename Limit>
		class safe_type_common
		{
		public:
			using raw_type = T;

		private:
			T value;

		public:
			explicit constexpr safe_type_common(T const& value)
				: value{Limit::apply(value)}
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
	}  // namespace detail

	namespace safe_type_limit
	{
		struct none
		{
			template <typename T>
			static constexpr T const& apply(T const& value)
			{
				return value;
			}
		};

		template <typename T, T min, T max>
		class range
		{
			static_assert(min < max, "Invalid range for safe_type");

			static T constexpr min_limit(T const& value)
			{
				return (value < min) ? min : value;
			}

			static T constexpr max_limit(T const& value)
			{
				return (value > max) ? max : value;
			}

		public:
			static T constexpr apply(T const& value)
			{
				return min_limit(max_limit(value));
			}
		};
	}  // namespace safe_type_limit

	template <typename Tag, typename T, typename Limit,
			  template <typename> class... Operation>
	class EBCO safe_type_limited
		: public detail::safe_type_common<T, Limit>,
		  public Operation<safe_type_limited<Tag, T, Limit, Operation...>>...
	{
	public:
		explicit constexpr safe_type_limited(T const& value)
			: detail::safe_type_common<T, Limit>(value)
		{
		}

		using type = safe_type_limited<Tag, T, Limit, Operation...>;

		// Allow construct from r-value and assign to l-value but do not
		// allow assign to r-value as it will make code that doesn't make sense
		// like `a + b = c` valid.
		safe_type_limited(type&&) = default;
		safe_type_limited(type const&) = default;
		type& operator=(type const&) & = default;
#if !defined(_MSC_VER)
		type& operator=(type&&) & = default;

		type& operator=(type const&) && = delete;
#endif  // !defined(_MSC_VER)
		type& operator=(type&&) && = delete;
	};

	template <typename Tag, typename T, template <typename> class... Operation>
	using safe_type =
		safe_type_limited<Tag, T, safe_type_limit::none, Operation...>;

	template <typename Derived, typename T, typename Limit,
			  template <typename> class... Operation>
	class EBCO extendable_safe_type_limited
		: public detail::safe_type_common<T, Limit>,
		  public Operation<Derived>...
	{
	public:
		explicit constexpr extendable_safe_type_limited(T const& value)
			: detail::safe_type_common<T, Limit>(value)
		{
		}
	};

	template <typename Derived, typename T,
			  template <typename> class... Operation>
	using extendable_safe_type =
		extendable_safe_type_limited<Derived, T, safe_type_limit::none,
									 Operation...>;

	namespace safe_type_operation
	{
		template <typename T>
		struct add : crtp<T, add<T>>
		{
			T operator+(T const& right) const
			{
				return T(this->derived_object().raw_value() +
						 right.raw_value());
			}
		};

		template <typename T>
		struct subtract : crtp<T, subtract<T>>
		{
			T operator-(T const& right) const
			{
				return T(this->derived_object().raw_value() -
						 right.raw_value());
			}
		};

		template <typename T>
		struct multiply : crtp<T, subtract<T>>
		{
			T operator*(T const& right) const
			{
				return T(this->derived_object().raw_value() *
						 right.raw_value());
			}
		};

		template <typename T>
		struct divide : crtp<T, subtract<T>>
		{
			T operator/(T const& right) const
			{
				return T(this->derived_object().raw_value() /
						 right.raw_value());
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
		struct postincrement : crtp<T, preincrement<T>>
		{
			T& operator++(int)
			{
				this->derived_object().raw_value()++;
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

		template <typename U>
		struct explicitly_convert_to
		{
			template <typename T>
			struct operation : crtp<T, operation<T>>
			{
				explicit operator U() const
				{
					return U{this->derived_object().raw_value()};
				}
			};
		};
	}  // namespace safe_type_operation
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H
