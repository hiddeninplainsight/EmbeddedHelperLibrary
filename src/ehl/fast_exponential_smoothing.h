#ifndef EMBEDDEDHELPERLIBRARY_FAST_EXPONENTIAL_SMOOTHING_H
#define EMBEDDEDHELPERLIBRARY_FAST_EXPONENTIAL_SMOOTHING_H

namespace ehl
{
	template <unsigned int smoothing_factor, typename T = unsigned short,
			  typename stored_t = unsigned int>
	class fast_exponential_smoothing
	{
	private:
		stored_t stored;

		inline stored_t smoothed() const
		{
			return stored >> smoothing_factor;
		}

	public:
		fast_exponential_smoothing()
			: stored(0)
		{
		}
		T value() const
		{
			return static_cast<T>(smoothed());
		}
		operator T() const
		{
			return value();
		}
		void add_value(T value_to_add)
		{
			stored_t const stored_minus_smoothed = stored - smoothed();
			stored =
				stored_minus_smoothed + static_cast<stored_t>(value_to_add);
		}

		T operator()(T value_to_add)
		{
			add_value(value_to_add);
			return value();
		}
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_FAST_EXPONENTIAL_SMOOTHING_H
