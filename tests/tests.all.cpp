#include "unity_cpp.h"

static void RunAllTests()
{
}

int TestMain(int argc, char** argv)
{
	return UnityMain(argc, const_cast<const char**>(argv), RunAllTests);
}
