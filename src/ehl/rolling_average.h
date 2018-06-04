#ifndef EMBEDDEDHELPERLIBRARY_ROLLING_AVERAGE_H
#define EMBEDDEDHELPERLIBRARY_ROLLING_AVERAGE_H

#include <cstddef>

namespace ehl
{
	template <typename T, std::size_t numberOfElements, typename TTotal = T>
	class rolling_average
	{
	private:
		T data[numberOfElements];
		TTotal total;
		std::size_t index;

	public:
		rolling_average()
			: data()
			, total(0)
			, index(0)
		{
		}

		T value() const
		{
			return static_cast<T>(total / numberOfElements);
		}

		operator T() const
		{
			return value();
		}

		void add_value(T value_to_add)
		{
			total -= static_cast<TTotal>(data[index]);
			total += static_cast<TTotal>(value_to_add);

			data[index] = value_to_add;

			++index;
			index %= numberOfElements;
		}

		T operator()(T value_to_add)
		{
			add_value(value_to_add);
			return value();
		}
	};
}

#endif  // EMBEDDEDHELPERLIBRARY_ROLLING_AVERAGE_H
