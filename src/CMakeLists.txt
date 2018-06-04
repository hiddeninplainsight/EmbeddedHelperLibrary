add_library(EmbeddedHelperLibrary INTERFACE)

target_include_directories(EmbeddedHelperLibrary INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
	)
