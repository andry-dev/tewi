cmake_minimum_required(VERSION 3.9)

project(tewi_examples)

message(STATUS "[tewi] Building examples")

add_executable(window-events window_events.cpp)
set_target_properties(window-events
	PROPERTIES
	CXX_STANDARD 14
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")
target_link_libraries(window-events PUBLIC tewi)

add_executable(imgui-example imgui.cpp)
set_target_properties(imgui-example
	PROPERTIES
	CXX_STANDARD 14
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")
target_link_libraries(imgui-example PUBLIC tewi)
