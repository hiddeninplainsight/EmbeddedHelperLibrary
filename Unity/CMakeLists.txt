add_library(unity
	Unity/src/unity.c
	Unity/src/unity.h
	Unity/src/unity_internals.h
	Unity/extras/fixture/src/unity_fixture.c
	Unity/extras/fixture/src/unity_fixture.h
	Unity/extras/fixture/src/unity_fixture_internals.h
	Unity/extras/fixture/src/unity_fixture_malloc_overrides.h
	unity_cpp.h
	)

add_library(ehl::unity ALIAS unity)

target_include_directories(unity PUBLIC
	Unity/src/
	Unity/extras/fixture/src/
	./
	)
