#ifndef EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H
#define EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H

#include "compiler_help/empty_base_class_optimisation.h"
#include "crtp.h"

namespace ehl
{
	template <typename T, typename Tag, template <typename> class... Operation>
	class EBCO safe_type : public Operation<safe_type<T, Tag, Operation...>>...
	{
	public:
		using raw_type = T;

	private:
		T value;

	public:
		explicit constexpr safe_type(T const& value)
			: value(value)
		{
		}

		T& get()
		{
			return value;
		}

		constexpr T const& get() const
		{
			return value;
		}
	};

	namespace safe_type_operation
	{
		template <typename T>
		struct add : crtp<T, add<T>>
		{
			T operator+(T const& right) const
			{
				return T(this->derived_object().get() + right.get());
			}
		};

		template <typename T>
		struct subtract : crtp<T, subtract<T>>
		{
			T operator-(T const& right) const
			{
				return T(this->derived_object().get() - right.get());
			}
		};

		template <typename T>
		struct preincrement : crtp<T, preincrement<T>>
		{
			T& operator++()
			{
				++this->derived_object().get();
				return this->derived_object();
			}
		};

		template <typename T>
		struct equal : crtp<T, equal<T>>
		{
			bool operator==(T const& other) const
			{
				return this->derived_object().get() == other.get();
			}
		};

		template <typename T>
		struct not_equal : crtp<T, not_equal<T>>
		{
			bool operator!=(T const& other) const
			{
				return this->derived_object().get() != other.get();
			}
		};

		template <typename T>
		struct less_than : crtp<T, less_than<T>>
		{
			bool operator<(T const& other) const
			{
				return this->derived_object().get() < other.get();
			}
		};

		template <typename T>
		struct less_than_or_equal : crtp<T, less_than_or_equal<T>>
		{
			bool operator<=(T const& other) const
			{
				return this->derived_object().get() <= other.get();
			}
		};

		template <typename T>
		struct greater_than : crtp<T, greater_than<T>>
		{
			bool operator>(T const& other) const
			{
				return this->derived_object().get() > other.get();
			}
		};

		template <typename T>
		struct greater_than_or_equal : crtp<T, greater_than_or_equal<T>>
		{
			bool operator>=(T const& other) const
			{
				return this->derived_object().get() >= other.get();
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
					return U{this->derived_object().get()};
				}
			};
		};
	}
}

#endif  // EMBEDDEDHELPERLIBRARY_SAFE_TYPE_H
