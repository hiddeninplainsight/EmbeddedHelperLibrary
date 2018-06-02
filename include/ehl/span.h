#ifndef EMBEDDEDHELPERLIBRARY_SPAN_H
#define EMBEDDEDHELPERLIBRARY_SPAN_H

#include <cstddef>
#include "type_traits/enable_if.h"
#include "type_traits/is_container.h"

namespace ehl
{
	template <typename T, typename iteratorT = T*>
	class span
	{
	public:
		using value_type = T;
		using reference = T&;
		using const_reference = reference const;

		using iterator = iteratorT;
		using const_iterator = iterator const;

		using size_type = std::size_t;

	private:
		iterator dataBegin;
		iterator dataEnd;

	public:
		span(iterator begin, size_type length)
			: dataBegin(begin)
			, dataEnd(begin + length)
		{
		}

		span(iterator begin, iterator end)
			: dataBegin(begin)
			, dataEnd(end)
		{
		}
		template <typename Cont>
		span(Cont& cont,
			 typename type_traits::enable_if<
				 type_traits::is_container<Cont>::value, int>::type = 0)
			: dataBegin(&cont[0])
			, dataEnd(&cont[0] + cont.size())
		{
		}

		template <std::size_t length>
		span(T (&data)[length])
			: dataBegin(data)
			, dataEnd(data + length)
		{
		}

		friend class span<const value_type>;

		template <typename U>
		span(span<U> const& other)
			: dataBegin(other.dataBegin)
			, dataEnd(other.dataEnd)
		{
		}

		template <typename U>
		span<T>& operator=(span<U> const& other)
		{
			dataBegin = other.dataBegin;
			dataEnd = other.dataEnd;
			return *this;
		}

		size_type length() const
		{
			return dataEnd - dataBegin;
		}
		iterator begin()
		{
			return dataBegin;
		}
		const_iterator begin() const
		{
			return dataBegin;
		}
		const_iterator cbegin() const
		{
			return dataBegin;
		}
		iterator end()
		{
			return dataEnd;
		}
		const_iterator end() const
		{
			return dataEnd;
		}
		const_iterator cend() const
		{
			return dataEnd;
		}
		reference operator[](size_type index)
		{
			return dataBegin[index];
		}
		const_reference operator[](size_type index) const
		{
			return dataBegin[index];
		}
	};
}

#endif  // EMBEDDEDHELPERLIBRARY_SPAN_H
