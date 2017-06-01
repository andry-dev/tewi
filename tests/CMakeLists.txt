cmake_minimum_required(VERSION 3.3)

project(tewi_tests)

add_executable(test-window src/window.cpp)

set_target_properties(test-window
	PROPERTIES
	CXX_STANDARD 14
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/tests"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/tests"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")

target_include_directories(test-window PRIVATE
	${PROJECT_SOURCE_DIR}/Catch/include)

add_test(tewi-window tewi-window)

target_link_libraries(test-window tewi)
