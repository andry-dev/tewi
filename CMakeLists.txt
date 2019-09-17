cmake_minimum_required(VERSION 3.13)
project(tewi)

option(TEWI_BUILD_TESTS "Build tewi's tests" OFF)
option(TEWI_BUILD_EXAMPLES "Build tewi's examples" OFF)
option(TEWI_BUILD_DOC "Build tewi's documentation" OFF)
option(TEWI_ENABLE_VULKAN "Enable Vulkan support" OFF)
option(TEWI_USE_TOOLS "Enable use of various tools on tewi's code" OFF)
option(TEWI_ENABLE_LTO "Enable Link Time Optimization if possible" OFF)
option(TEWI_CLANG_FORMAT_PRE_BUILD "Run clang-format before building tewi" OFF)
option(TEWI_INTEGRATE_IMGUI "Integrate ImGui tewi" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

add_subdirectory(external)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
include(CheckIPOSupported)

set(SRC
    src/Input/InputBuffer.cpp
    src/Physics/Collidable2D.cpp
    src/Utils/Clock.cpp
    src/Utils/TickTimer.cpp
    src/Video/Camera2D.cpp
    src/Platform/OpenGL/BatchRenderer2D.cpp
    src/Platform/OpenGL/Context.cpp
    src/Platform/OpenGL/Device.cpp
    src/Platform/OpenGL/IndexBuffer.cpp
    src/Platform/OpenGL/Instance.cpp
    src/Platform/OpenGL/Shader.cpp
    src/Platform/OpenGL/Swapchain.cpp
    src/Platform/OpenGL/TextureCache.cpp
    src/Platform/OpenGL/ImGuiBindings.cpp
    src/Platform/OpenGL/imgui_impl_opengl3.cpp
    src/Platform/OpenGL/imgui_impl_glfw.cpp
    src/Platform/NullRenderer/BatchRenderer2D.cpp
    src/Platform/NullRenderer/Context.cpp
    src/Platform/NullRenderer/Swapchain.cpp
    src/Platform/NullRenderer/Window.cpp
    src/Platform/NullRenderer/Device.cpp
)

add_library(${PROJECT_NAME} ${SRC})

include(cmake/set-flags.cmake)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/>)

include(cmake/link-deps.cmake)

if (TEWI_USE_TOOLS)
    include(cmake/include-tools.cmake)
endif()

if (TEWI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (TEWI_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (TEWI_BUILD_DOC)
    add_subdirectory(doc)
endif()

include(cmake/install-target.cmake)
