cmake_minimum_required(VERSION 3.9)

project(tewi_examples)

message(STATUS "[tewi] Building examples")
set(TEWI_EXAMPLES_BUILD_DIR "${PROJECT_BINARY_DIR}/bin")

function(new_target target_name)
    add_executable(${target_name} ${ARGV1})

    if (MSVC)
    else()
        target_compile_options(${target_name}
            PRIVATE
            -Wall -Wextra -pedantic -Wpedantic)

        if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
            target_compile_options(${target_name}
                PRIVATE
                -Weverything -Wno-missing-prototypes)
        endif()
    endif()

    set_target_properties(${target_name}
        PROPERTIES
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY "${TEWI_EXAMPLES_BUILD_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TEWI_EXAMPLES_BUILD_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${TEWI_EXAMPLES_BUILD_DIR}")

    if (TEWI_ENABLE_LTO)
        check_ipo_supported(RESULT should_lto)
        if (should_lto)
            set_property(TARGET ${target_name}
                PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
        endif()
    endif()

    target_link_libraries(${target_name} PUBLIC tewi)
endfunction()


new_target(window-events window_events.cpp)
new_target(imgui-example imgui.cpp)
new_target(sprite-rendering sprite_rendering.cpp)
