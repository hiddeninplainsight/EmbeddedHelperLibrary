#ifndef EMBEDDEDHELPERLIBRARY_OPTIONAL_H
#define EMBEDDEDHELPERLIBRARY_OPTIONAL_H

#include <new>

#include "rvalue.h"
#include "type_traits/detection_compiler_generated_methods.h"
#include "type_traits/detection_idiom.h"
#include "type_traits/enable_if.h"

namespace ehl
{
	template<typename T>
	class optional
	{
	private:
		alignas(alignof(T)) unsigned char valueData[sizeof(T)];
		bool valid{false};

		inline void destroy_object_if_it_exists()
		{
			if (valid)
			{
				reinterpret_cast<T*>(valueData)->~T();
			}
		}

	public:
		optional() = default;

		optional(optional const& other)
			: valid{other.valid}
		{
			if (valid)
			{
				new(valueData) T{other.value()};
			}
		}

		optional(optional&& other)
			: valid{other.valid}
		{
			if (valid)
			{
				new(valueData) T{::ehl::as_rvalue(other.value())};
			}
		}

		optional(T const& object)
			: valid{true}
		{
			new(valueData) T{object};
		}

		optional(T&& object)
			: valid{true}
		{
			new(valueData) T{::ehl::as_rvalue(object)};
		}

		~optional()
		{
			destroy_object_if_it_exists();
		}

		template<typename U = T>
		::ehl::enable_if_t<
			(::ehl::is_move_constructable<U>::value == false) ||
			(::ehl::is_move_assignable<U>::value == false),
			optional&>
		 operator=(optional&& other) = delete;

		template<typename U = T>
		::ehl::enable_if_t<
			::ehl::is_move_constructable<U>::value &&
			::ehl::is_move_assignable<U>::value,
			optional&>
		operator=(optional&& other)
		{
			if(other.valid)
			{
				if(valid)
				{
					value() = ::ehl::as_rvalue(other.value());
				}
				else
				{
					new(valueData) T{::ehl::as_rvalue(other.value())};
				}
			}
			else
			{
				destroy_object_if_it_exists();
			}
			valid = other.valid;
			return *this;
		}

		optional& operator=(T const& other)
		{
			if (valid)
			{
				value() = other;
			}
			else
			{
				new(valueData) T{other};
				valid = true;
			}
			return *this;
		}

		bool is_valid() const
		{
			return valid;
		}

		T& value()
		{
			return *reinterpret_cast<T*>(valueData);
		}

		T const& value() const
		{
			return *reinterpret_cast<T const*>(valueData);
		}
	};
}

#endif //EMBEDDEDHELPERLIBRARY_OPTIONAL_H
