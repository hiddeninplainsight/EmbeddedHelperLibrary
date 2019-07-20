#ifndef EMBEDDEDHELPERLIBRARY_ISR_WRITTEN_VARIABLE_H
#define EMBEDDEDHELPERLIBRARY_ISR_WRITTEN_VARIABLE_H

#include "rvalue.h"

namespace ehl
{
	template<typename T>
	class isr_written_variable
	{
	private:
		mutable volatile bool modified;
		volatile T value;

	public:
		isr_written_variable() = default;

		isr_written_variable(T initial_value)
			:value{as_rvalue(initial_value)}
		{
		}

		isr_written_variable& operator=(isr_written_variable const& other)
		{
			value = other.value;
			modified = true;
			return *this;
		}

		isr_written_variable<T>& operator=(T new_value)
		{
			value = as_rvalue(new_value);
			modified = true;
			return *this;
		}

		operator T() const
		{
			modified = false;
			T v = value;
			while(modified)
			{
				modified = false;
				v = value;
			}
			return v;
		}
	};
}

#endif //EMBEDDEDHELPERLIBRARY_ISR_WRITTEN_VARIABLE_H
