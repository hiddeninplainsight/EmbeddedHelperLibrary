cmake_minimum_required(VERSION 3.2)
project(EmbeddedHelperLibrary)

set(CMAKE_CXX_STANDARD 11)

if(${UNIX})
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror -fno-rtti -fno-exceptions")
endif(${UNIX})

add_subdirectory(include)
add_subdirectory(Unity)
add_subdirectory(tests)
