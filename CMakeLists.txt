cmake_minimum_required(VERSION 3.2)
project(EmbeddedHelperLibrary)

if(${UNIX})

	set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")

endif(${UNIX})

add_subdirectory(Unity)
add_subdirectory(tests)
