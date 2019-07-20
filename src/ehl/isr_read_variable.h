#ifndef EMBEDDEDHELPERLIBRARY_ISR_READ_VARIABLE_H
#define EMBEDDEDHELPERLIBRARY_ISR_READ_VARIABLE_H

#include "rvalue.h"

namespace ehl
{
	template<typename T>
	class isr_read_variable
	{
	private:
		volatile bool use_a{true};
		volatile T value_a;
		volatile T value_b;

	public:
		isr_read_variable() = default;

		isr_read_variable(T initial_value)
			:value_a{as_rvalue(initial_value)}
		{
		}

		isr_read_variable& operator=(isr_read_variable const& other)
		{
			if(use_a)
			{
				value_b = other;
			}
			else
			{
				value_a = other;
			}
			use_a = !use_a;
			return *this;
		}

		isr_read_variable<T>& operator=(T new_value)
		{
			if(use_a)
			{
				value_b = new_value;
			}
			else
			{
				value_a = new_value;
			}
			use_a = !use_a;
			return *this;
		}

		operator T() const
		{
			return use_a ? value_a : value_b;
		}
	};
}

#endif //EMBEDDEDHELPERLIBRARY_ISR_READ_VARIABLE_H
