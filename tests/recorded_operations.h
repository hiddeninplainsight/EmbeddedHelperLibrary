#ifndef EMBEDDEDHELPERLIBRARYTESTS_RECORDED_OPERATIONS_H
#define EMBEDDEDHELPERLIBRARYTESTS_RECORDED_OPERATIONS_H

class record_operations
{
public:
	bool defaultConstructed{false};
	bool copyConstructed{false};
	bool moveConstructed{false};
	static int globalCopyConstructCount;
	static int globalCopyAssignCount;
	static int globalMoveConstructCount;
	static int globalMoveAssignCount;
	bool copyAssigned{false};
	bool moveAssigned{false};
	bool* destructed{nullptr};

	record_operations()
		: defaultConstructed{true}
	{
	}

	explicit record_operations(bool* destructed)
		: destructed{destructed}
	{
	}

	record_operations(record_operations const& other)
		: copyConstructed{true}
		, destructed{other.destructed}
	{
		++globalCopyConstructCount;
	}

	record_operations(record_operations&& other)
		: moveConstructed{true}
		, destructed{other.destructed}
	{
		++globalMoveConstructCount;
	}

	record_operations& operator=(record_operations const&)
	{
		++globalCopyAssignCount;
		copyAssigned = true;
		return *this;
	}

	record_operations& operator=(record_operations&&)
	{
		++globalMoveAssignCount;
		moveAssigned = true;
		return *this;
	}

	~record_operations()
	{
		if (destructed)
			*destructed = true;
	}

	static void ClearCounters()
	{
		globalCopyConstructCount = 0;
		globalCopyAssignCount = 0;
		globalMoveConstructCount = 0;
		globalMoveAssignCount = 0;
	}
};

#endif //EMBEDDEDHELPERLIBRARYTESTS_RECORDED_OPERATIONS_H
