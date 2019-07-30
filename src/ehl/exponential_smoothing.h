#ifndef EMBEDDEDHELPERLIBRARY_EXPONENTIAL_SMOOTHING_H
#define EMBEDDEDHELPERLIBRARY_EXPONENTIAL_SMOOTHING_H

namespace ehl
{
	template <typename T>
	class exponential_smoothing
	{
	private:
		T const smoothing_factor;
		T const smoothing_one;

		T current_value;

	public:
		// smoothing_factor should be between 0 and 1.
		// A smaller smoothing factor gives more smoothing
		explicit exponential_smoothing(T smoothing_factor, T smoothing_one = 1)
			: smoothing_factor(smoothing_factor)
			, smoothing_one(smoothing_one)
			, current_value()
		{
		}

		T value() const
		{
			return current_value;
		}
		operator T() const
		{
			return value();
		}
		void add_value(T value_to_add)
		{
			T const old_value_factor = smoothing_one - smoothing_factor;
			current_value = (current_value * old_value_factor) / smoothing_one;
			current_value += (value_to_add * smoothing_factor) / smoothing_one;
		}

		T operator()(T value_to_add)
		{
			add_value(value_to_add);
			return value();
		}
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_EXPONENTIAL_SMOOTHING_H
