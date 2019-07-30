#ifndef EMBEDDEDHELPERLIBRARY_ROLLING_AVERAGE_WITH_EVENT_H
#define EMBEDDEDHELPERLIBRARY_ROLLING_AVERAGE_WITH_EVENT_H

#include "events.h"
#include "rolling_average.h"

namespace ehl
{
	template <typename T, std::size_t numberOfElements, typename TTotal = T>
	class rolling_average_with_event
	{
	private:
		rolling_average<T, numberOfElements, TTotal> average;

	public:
		event<T> average_update;

		operator T() const
		{
			return average;
		}

		void add_value(T value)
		{
			average.add_value(value);

			average_update.raise(average);
		}
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_ROLLING_AVERAGE_WITH_EVENT_H
