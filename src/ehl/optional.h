#ifndef EMBEDDEDHELPERLIBRARY_OPTIONAL_H
#define EMBEDDEDHELPERLIBRARY_OPTIONAL_H

#include <new>

#include "rvalue.h"

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
			if(valid)
			{
				new(valueData) T{other.value()};
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

		optional& operator=(T const& other)
		{
			if(valid)
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
