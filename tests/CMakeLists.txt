cmake_minimum_required(VERSION 3.3)

project(tewi_tests)

message(STATUS "[tewi] Building tests")

add_executable(test-window src/window.cpp)

set_target_properties(test-window
	PROPERTIES
	CXX_STANDARD 14
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin"
    )



add_test(
	NAME Window
    COMMAND $<TARGET_FILE:test-window>)

target_link_libraries(test-window tewi)
