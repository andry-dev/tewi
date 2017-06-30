cmake_minimum_required(VERSION 3.3)

project(tewi_tests)

message(STATUS "[tewi] Building tests")

add_executable(test-window src/window.cpp)

set_target_properties(test-window
	PROPERTIES
	CXX_STANDARD 14)

target_include_directories(test-window
	PRIVATE
	${PROJECT_SOURCE_DIR}/Catch/include)

add_test(
	NAME Window
	COMMAND tewi-window)

target_link_libraries(test-window tewi)
