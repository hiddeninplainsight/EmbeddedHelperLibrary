#ifndef EMBEDDEDHELPERLIBRARY_EVENTS_H
#define EMBEDDEDHELPERLIBRARY_EVENTS_H

namespace ehl
{
	// Event handler base for event with parameter
	template <typename TParameter>
	class event_handler_base
	{
	public:
		using parameter_type = TParameter;

		virtual ~event_handler_base() {}
		virtual void invoke(TParameter parameter) const = 0;
	};

	// Event handler base for event with no parameter
	template <>
	class event_handler_base<void>
	{
	public:
		using parameter_type = void;

		virtual ~event_handler_base() {}
		virtual void invoke() const = 0;
	};

	// Event with parameter
	template <typename TParameter>
	class event
	{
	public:
		using handler_type = event_handler_base<TParameter> const;

	private:
		handler_type* handler{nullptr};

	public:
		void set_handler(handler_type* eventHandler)
		{
			handler = eventHandler;
		}

		void clear_handler()
		{
			handler = nullptr;
		}

		void raise(TParameter parameter) const
		{
			if (handler != 0)
				handler->invoke(parameter);
		}
	};

	// Event with no parameter
	template <>
	class event<void>
	{
	public:
		using handler_type = event_handler_base<void> const;

	private:
		handler_type* handler{nullptr};

	public:
		void set_handler(handler_type* eventHandler)
		{
			handler = eventHandler;
		}

		void clear_handler()
		{
			handler = 0;
		}

		void raise() const
		{
			if (handler != 0)
				handler->invoke();
		}
	};

	// Event handler for member function with parameter
	template <typename TObject, typename TParameter>
	class event_handler : public event_handler_base<TParameter>
	{
	public:
		using parameter_type = TParameter;
		using object_type = TObject;
		using member_function_pointer = void (object_type::*)(parameter_type);

	private:
		object_type* object;
		member_function_pointer function;

	public:
		event_handler(object_type& object, member_function_pointer function)
			: object(&object)
			, function(function)
		{
		}

		virtual void invoke(parameter_type parameter) const
		{
			(object->*function)(parameter);
		}
	};

	// Event handler for member function with no parameter
	template <typename TObject>
	class event_handler<TObject, void> : public event_handler_base<void>
	{
	public:
		using object_type = TObject;
		using member_function_pointer = void (object_type::*)();

	private:
		object_type* object;
		member_function_pointer function;

	public:
		event_handler(object_type& object, member_function_pointer function)
			: object(&object)
			, function(function)
		{
		}

		virtual void invoke() const
		{
			(object->*function)();
		}
	};

	// Event handler for normal function with parameter
	template <typename TParameter>
	class event_handler<void, TParameter>
		: public event_handler_base<TParameter>
	{
	public:
		using parameter_type = TParameter;
		using function_pointer = void (*)(parameter_type);

	private:
		function_pointer function;

	public:
		event_handler(function_pointer function)
			: function(function)
		{
		}
		virtual void invoke(parameter_type parameter) const
		{
			(*function)(parameter);
		}
	};

	// Event handler for normal function with no parameter
	template <>
	class event_handler<void, void> : public event_handler_base<void>
	{
	public:
		using function_pointer = void (*)();

	private:
		function_pointer function;

	public:
		event_handler(function_pointer function)
			: function(function)
		{
		}
		virtual void invoke() const
		{
			(*function)();
		}
	};
}  // namespace ehl

#endif  // EMBEDDEDHELPERLIBRARY_EVENTS_H
