#ifndef EMBEDDEDHELPERLIBRARY_CIRCULAR_BUFFER_H
#define EMBEDDEDHELPERLIBRARY_CIRCULAR_BUFFER_H

#include <cstdlib>

namespace ehl
{
	template<typename T, size_t buffer_elements>
	class isr_circular_buffer
	{
	private:
		volatile size_t head{0};
		volatile size_t tail{0};
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

		size_t length() const;
		bool push(T value);
		popped_value pop();
	};

	template<typename T, size_t buffer_elements>
	size_t isr_circular_buffer<T, buffer_elements>::length() const
	{
		if(tail > head)
			return (buffer_elements - tail) + head;
		return head - tail;
	}

	template<typename T, size_t buffer_elements>
	bool isr_circular_buffer<T, buffer_elements>::push(T value)
	{
		size_t next_head = (head + 1) % buffer_elements;

		if(next_head == tail)
			return false;

		buffer[head] = value;
		head = next_head;
		return true;
	}

	template<typename T, size_t buffer_elements>
	auto isr_circular_buffer<T, buffer_elements>::pop() -> popped_value
	{
		if(tail == head)
		{
			return popped_value{};
		}

		popped_value v{ true, buffer[tail] };
		tail = (tail + 1) % buffer_elements;
		return v;
	}
}

#endif //EMBEDDEDHELPERLIBRARY_CIRCULAR_BUFFER_H
