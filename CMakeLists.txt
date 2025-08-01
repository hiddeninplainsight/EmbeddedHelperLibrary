cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED PROJECT_NAME)
	set(NOT_SUBPROJECT ON)
endif()

project(EmbeddedHelperLibrary)

if(NOT_SUBPROJECT)
	set(CMAKE_CXX_STANDARD 11)

	if(${UNIX})
		set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror -fno-rtti -fno-exceptions")
	endif(${UNIX})
endif(NOT_SUBPROJECT)

add_subdirectory(src)
add_subdirectory(Unity)
add_subdirectory(tests)
