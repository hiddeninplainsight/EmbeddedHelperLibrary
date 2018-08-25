#ifndef EMBEDDEDHELPERLIBRARY_EITHER_H
#define EMBEDDEDHELPERLIBRARY_EITHER_H

#include <new>

namespace ehl
{
	template<typename T1, typename T2>
	class either
	{
	private:
		unsigned int valid_type{0};

		alignas(T1) alignas(T2) unsigned char value[sizeof(T1) > sizeof(T2) ? sizeof(T1) : sizeof(T2)];

		bool is(T1*)
		{
			return valid_type == 1;
		}

		bool is(T2*)
		{
			return valid_type == 2;
		}

		void delete_object()
		{
			switch(valid_type)
			{
				case 1:
					reinterpret_cast<T1*>(value)->~T1();
					break;
				case 2:
					reinterpret_cast<T2*>(value)->~T2();
					break;
				default:
					break;
			}
		}
	public:
		template<typename T>
		bool is()
		{
			return is(static_cast<T*>(nullptr));
		}

		void set(T1 const& v)
		{
			delete_object();
			new(value) T1{v};
			valid_type = 1;
		}

		void set(T2 const& v)
		{
			delete_object();
			new(value) T2{v};
			valid_type = 2;
		}

		explicit operator T1 const&()
		{
			return *reinterpret_cast<T1*>(value);
		}

		explicit operator T2 const&()
		{
			return *reinterpret_cast<T2*>(value);
		}
	};
}

#endif //EMBEDDEDHELPERLIBRARY_EITHER_H
