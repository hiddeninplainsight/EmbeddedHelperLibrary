#ifndef EMBEDDEDHELPERLIBRARY_CIRCULAR_BUFFER_H
#define EMBEDDEDHELPERLIBRARY_CIRCULAR_BUFFER_H

namespace ehl
{
	using isr_circular_buffer_size_t = unsigned int;

	template <typename T, isr_circular_buffer_size_t buffer_elements>
	class isr_circular_buffer
	{
	private:
		volatile isr_circular_buffer_size_t head{0};
		volatile isr_circular_buffer_size_t tail{0};
		volatile T buffer[buffer_elements];

	public:
		struct popped_value
		{
			bool valid{false};
			T value;

			popped_value() = default;

			popped_value(bool valid, T value)
				: valid{valid}
				, value{value}
			{
			}
		};

		isr_circular_buffer_size_t length() const;
		bool push(T value);
		popped_value pop();
	};

	template <typename T, isr_circular_buffer_size_t buffer_elements>
	isr_circular_buffer_size_t isr_circular_buffer<T, buffer_elements>::length()
		const
	{
		if (tail > head)
			return (buffer_elements - tail) + head;
		return head - tail;
	}

	template <typename T, isr_circular_buffer_size_t buffer_elements>
	bool isr_circular_buffer<T, buffer_elements>::push(T value)
	{
		isr_circular_buffer_size_t next_head = (head + 1) % buffer_elements;

		if (next_head == tail)
			return false;

		buffer[head] = value;
		head = next_head;
		return true;
	}

	template <typename T, isr_circular_buffer_size_t buffer_elements>
	auto isr_circular_buffer<T, buffer_elements>::pop() -> popped_value
	{
		if (tail == head)
		{
			return popped_value{};
		}

		popped_value v{true, buffer[tail]};
		tail = (tail + 1) % buffer_elements;
		return v;
	}
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_CIRCULAR_BUFFER_H
