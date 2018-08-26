#ifndef EMBEDDEDHELPERLIBRARY_EITHER_H
#define EMBEDDEDHELPERLIBRARY_EITHER_H

#include <new>
#include "rvalue.h"

namespace ehl
{
	namespace detail
	{
		template<unsigned int index, typename T, typename... Tother>
		class either_functions : public either_functions<index + 1, Tother...>
		{
		private:
			using base = either_functions<index + 1, Tother...>;

		protected:
			using base::valid_type;
			using base::is;
			using base::delete_object;
			using base::data;
			using base::as;

			bool is(T *)
			{
				return valid_type == index;
			}

			void delete_object(unsigned char *value)
			{
				if (valid_type == index)
				{
					reinterpret_cast<T *>(value)->~T();
				}
				else
				{
					base::delete_object(value);
				}
			}

			T& as(T *)
			{
				return *reinterpret_cast<T *>(data());
			}

		public:
			using base::set;

			void set(T const &v)
			{
				delete_object();
				valid_type = 0;
				new(data()) T{v};
				valid_type = index;
			}

			void set(T&& v)
			{
				delete_object();
				valid_type = 0;
				new(data()) T(::ehl::forward<T>(v));
				valid_type = index;
			}
		};

		template<unsigned int index, typename T>
		class either_functions<index, T>
		{
		protected:
			unsigned int valid_type{0};

			virtual void delete_object() = 0;
			virtual unsigned char *data() = 0;

			bool is(T *)
			{
				return valid_type == index;
			}

			void delete_object(unsigned char *value)
			{
				if (valid_type == index)
				{
					reinterpret_cast<T *>(value)->~T();
				}
			}

			T& as(T *)
			{
				return *reinterpret_cast<T *>(data());
			}

		public:
			void set(T const &v)
			{
				delete_object();
				valid_type = 0;
				new(data()) T{v};
				valid_type = index;
			}

			void set(T&& v)
			{
				delete_object();
				valid_type = 0;
				new(data()) T(::ehl::forward<T>(v));
				valid_type = index;
			}
		};

		template<typename T, typename... Tother>
		struct largest_type
		{
			static ::std::size_t constexpr size =
				sizeof(T) > largest_type<Tother...>::size ? sizeof(T)
														  : largest_type<Tother...>::size;
			static auto constexpr alignment =
				alignof(T) > largest_type<Tother...>::alignment ? alignof(T)
														  : largest_type<Tother...>::alignment;

		};

		template<typename T>
		struct largest_type<T>
		{
			static ::std::size_t constexpr size = sizeof(T);
			static auto constexpr alignment = alignof(T);
		};
	}

	template<typename... T>
	class either : detail::either_functions<1, T...>
	{
	protected:
		alignas(detail::largest_type<T...>::alignment) unsigned char value[detail::largest_type<T...>::size];

		using base = detail::either_functions<1, T...>;

		using base::valid_type;
		using base::is;
		using base::as;

		unsigned char* data() override
		{
			return value;
		}

		void delete_object() override
		{
			if(valid_type != 0)
			{
				base::delete_object(value);
			}
		}
	public:
		either() = default;
		either(either const&) = delete;
		either& operator=(either const&) = delete;

		either(either&& other) noexcept
		{
			valid_type = other.valid_type;
			for(::std::size_t i = 0; i < sizeof(value); ++i)
			{
				value[i] = other.value[i];
			}
			other.valid_type = 0;
		}

		either& operator=(either&& other) noexcept
		{
			valid_type = other.valid_type;
			for(::std::size_t i = 0; i < sizeof(value); ++i)
			{
				value[i] = other.value[i];
			}
			other.valid_type = 0;

			return *this;
		}

		~either()
		{
			delete_object();
		}

		using base::set;

		template<typename U>
		bool is()
		{
			return is(static_cast<U*>(nullptr));
		}

		template<typename U>
		U& as()
		{
			return as(static_cast<U*>(nullptr));
		}
	};
}

#endif //EMBEDDEDHELPERLIBRARY_EITHER_H
