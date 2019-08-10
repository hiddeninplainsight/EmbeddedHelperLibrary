#ifndef EMBEDDEDHELPERLIBRARY_OPTIONAL_H
#define EMBEDDEDHELPERLIBRARY_OPTIONAL_H

#include <new>

#include "rvalue.h"
#include "type_traits/detection_compiler_generated_methods.h"
#include "type_traits/detection_idiom.h"
#include "type_traits/enable_if.h"

namespace ehl
{
	namespace detail
	{
		template<typename T>
		class optional_storage
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

		protected:
			optional_storage() = default;

			optional_storage(optional_storage const& other)
				: valid{other.valid}
			{
				if (valid)
				{
					new(valueData) T{other.value()};
				}
			}

			optional_storage(optional_storage&& other)
				: valid{other.valid}
			{
				if (valid)
				{
					new(valueData) T{::ehl::as_rvalue(other.value())};
				}
			}

			optional_storage(T const& object)
				: valid{true}
			{
				new(valueData) T{object};
			}

			optional_storage(T&& object)
				: valid{true}
			{
				new(valueData) T{::ehl::as_rvalue(object)};
			}

			~optional_storage()
			{
				destroy_object_if_it_exists();
			}

			optional_storage& operator=(optional_storage const& other)
			{
				if (other.valid)
				{
					if (valid)
					{
						value() = other.value();
					}
					else
					{
						new(valueData) T{other.value()};
					}
				}
				else
				{
					destroy_object_if_it_exists();
				}
				valid = other.valid;
				return *this;
			}

			optional_storage& operator=(optional_storage&& other)
			{
				if (other.valid)
				{
					if (valid)
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

			optional_storage& operator=(T const& other)
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

		public:
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
	}  // namespace detail

	template<typename T,
		bool copyable = ::ehl::is_copy_constructible<T>::value && ::ehl::is_copy_assignable<T>::value,
		bool movable = ::ehl::is_move_constructible<T>::value && ::ehl::is_move_assignable<T>::value
	>
	class optional;

	template<typename T>
	class optional<T, true, false> : public detail::optional_storage<T>
	{
	public:
		optional() = default;

		optional(T const& value)
			: detail::optional_storage<T>{value}
		{
		}

		optional& operator=(T const& other)
		{
			detail::optional_storage<T>::operator=(other);
			return *this;
		}

		optional(optional const& other)
			: detail::optional_storage<T>{other}
		{
		}

		optional& operator=(optional const& other)
		{
			detail::optional_storage<T>::operator=(other);
			return *this;
		}

		optional(optional&&) = delete;
		optional& operator=(optional&&) = delete;
	};

	template<typename T>
	class optional<T, false, true> : public detail::optional_storage<T>
	{
	public:
		optional() = default;

		optional(T&& value)
			: detail::optional_storage<T>{::ehl::as_rvalue(value)}
		{
		}

		optional(optional const&) = delete;
		optional& operator=(optional const& other) = delete;

		optional(optional&& other)
			: detail::optional_storage<T>{::ehl::as_rvalue(other)}
		{
		}

		optional& operator=(optional&& other)
		{
			detail::optional_storage<T>::operator=(::ehl::as_rvalue(other));
			return *this;
		}
	};

	template<typename T>
	class optional<T, true, true> : public detail::optional_storage<T>
	{
	public:
		optional() = default;

		optional(T const& value)
			: detail::optional_storage<T>{value}
		{
		}

		optional& operator=(T const& other)
		{
			detail::optional_storage<T>::operator=(other);
			return *this;
		}

		optional(T&& value)
			: detail::optional_storage<T>{::ehl::as_rvalue(value)}
		{
		}

		optional(optional const& other)
			: detail::optional_storage<T>{other}
		{
		}

		optional& operator=(optional const& other)
		{
			detail::optional_storage<T>::operator=(other);
			return *this;
		}

		optional(optional&& other)
			: detail::optional_storage<T>{::ehl::as_rvalue(other)}
		{
		}

		optional& operator=(optional&& other)
		{
			detail::optional_storage<T>::operator=(::ehl::as_rvalue(other));
			return *this;
		}
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_OPTIONAL_H
