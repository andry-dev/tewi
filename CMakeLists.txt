cmake_minimum_required(VERSION 3.12)
project(tewi)

option(TEWI_BUILD_TESTS "Build tewi's tests" OFF)
option(TEWI_BUILD_EXAMPLES "Build tewi's examples" OFF)
option(TEWI_ENABLE_VULKAN "Enable Vulkan support" OFF)
option(TEWI_USE_TOOLS "Enable use of various tools on tewi's code" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#add_subdirectory(lib/universal/glfw)
add_subdirectory(lib/universal/asl)
#add_subdirectory(lib/universal/glm)
#add_subdirectory(lib/universal)
add_subdirectory(doc)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)


set(SRC
    src/Input/InputBuffer.cpp
    src/Physics/Collidable2D.cpp
    src/Utils/Clock.cpp
    src/Utils/TickTimer.cpp
    src/Utils/stb.cpp
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
    src/Platform/NullRenderer/Shader.cpp
    src/Platform/NullRenderer/BatchRenderer2D.cpp
    src/Platform/NullRenderer/Context.cpp
    src/Platform/NullRenderer/Swapchain.cpp
    src/Platform/NullRenderer/Window.cpp
    src/Platform/NullRenderer/Device.cpp
    )




set(IN_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include/tewi)

set(PUBLIC_HEADERS
    ${IN_INCLUDE_DIR}/Common.h

    # Events
    ${IN_INCLUDE_DIR}/EventSystem/Event.h
    ${IN_INCLUDE_DIR}/EventSystem/EventType.h

    # Input/Output
    ${IN_INCLUDE_DIR}/IO/BasicIO.h
    ${IN_INCLUDE_DIR}/IO/InputManager.h

    # Input systems
    ${IN_INCLUDE_DIR}/Input/InputBuffer.hpp

    # Physics
    ${IN_INCLUDE_DIR}/Physics/Collidable2D.h

    # Utilities
    ${IN_INCLUDE_DIR}/Utils/Clock.h
    ${IN_INCLUDE_DIR}/Utils/Log.h
    ${IN_INCLUDE_DIR}/Utils/TickTimer.h

    # Drawing
    ${IN_INCLUDE_DIR}/Video/API/API.h
    ${IN_INCLUDE_DIR}/Video/API/Context.hpp
    ${IN_INCLUDE_DIR}/Video/API/Device.hpp
    ${IN_INCLUDE_DIR}/Video/API/Instance.hpp
    ${IN_INCLUDE_DIR}/Video/API/Swapchain.hpp
    ${IN_INCLUDE_DIR}/Video/BatchRenderer2D.hpp
    ${IN_INCLUDE_DIR}/Video/Camera2D.h
    ${IN_INCLUDE_DIR}/Video/IndexBuffer.hpp
    ${IN_INCLUDE_DIR}/Video/Renderable2D.hpp
    ${IN_INCLUDE_DIR}/Video/ResourceManager.hpp
    ${IN_INCLUDE_DIR}/Video/Shader.hpp
    ${IN_INCLUDE_DIR}/Video/Sprite.h
    ${IN_INCLUDE_DIR}/Video/Texture.h
    ${IN_INCLUDE_DIR}/Video/TextureCache.h
    ${IN_INCLUDE_DIR}/Video/TextureCache.hxx
    ${IN_INCLUDE_DIR}/Video/Uniform.h
    ${IN_INCLUDE_DIR}/Video/Vertex.h
    ${IN_INCLUDE_DIR}/Video/Window.hpp)

set(PRIVATE_HEADERS
    )

add_library(${PROJECT_NAME} ${SRC})

target_sources(${PROJECT_NAME}
    PUBLIC
    ${PUBLIC_HEADERS}
    PRIVATE
    ${PRIVATE_HEADERS})

if(MSVC)
    # Common
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        /W4 /std:c++latest /permissive- /GR-)

    # Release
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:RELEASE>:/Ob2 /Ot /GL /sdl- /LTCG>)
else()
    # Common
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall -Wextra -pedantic -Wpedantic
        -Weffc++ -Wno-unused-const-variable
         -pipe -fno-rtti)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME}
            PRIVATE
            -Weverything -Wno-missing-prototypes)
    endif()

    # Release
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:RELEASE>:-O3>)

    # Debug
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:DEBUG>:-fno-omit-frame-pointer>)
endif()


set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)


if (BUILD_SHARED_LIBS)
    message(STATUS "[tewi] Building as DLL/so")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        TEWI_SHARED_LIB=1 GLEW_BUILD)
    #add_definitions(-DGLEW_BUILD)
else()
    message(STATUS "[tewi] Building as LIB/a")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        TEWI_STATIC_LIB=1
        GLEW_STATIC)
    #add_definitions(-DGLEW_STATIC)
endif()

if (TEWI_ENABLE_VULKAN)
    message(STATUS "[tewi] Vulkan enabled")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        GLFW_INCLUDE_VULKAN
        TEWI_ENABLE_VULKAN)
else()
    message(STATUS "[tewi] Vulkan disabled")
endif()

if(WIN32)
    # Add GLEW
    set(GLEW_LIBRARIES
        ${PROJECT_SOURCE_DIR}/lib/msvc/glew/lib/Release/x64/glew32.lib)

    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/msvc/glew/include)

    if (TEWI_ENABLE_VULKAN)
        target_include_directories(
            ${PROJECT_NAME}
            PUBLIC
            ${PROJECT_SOURCE_DIR}/lib/msvc/vulkan/include)
    endif()

    set(VULKAN_LIBS
        ${PROJECT_SOURCE_DIR}/lib/msvc/vulkan/lib/vulkan-1.lib)

    set(WIN32_OPENGL_LIBS
        opengl32.lib)

else()
    set(VULKAN_LIBS vulkan)
endif()

target_include_directories(${PROJECT_NAME}
    SYSTEM
    PUBLIC
    ${PROJECT_SOURCE_DIR}/lib/universal/asl/include
    ${PROJECT_SOURCE_DIR}/lib/universal/glfw/include
    ${PROJECT_SOURCE_DIR}/lib/universal/glm
    ${PROJECT_SOURCE_DIR}/lib/universal/stb
    ${PROJECT_SOURCE_DIR}/lib/universal/imgui)



target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${WIN32_OPENGL_LIBS}
    CONAN_PKG::glew
    CONAN_PKG::glm
    CONAN_PKG::glfw
    CONAN_PKG::imgui
    CONAN_PKG::stb
    asl)

if (TEWI_ENABLE_VULKAN)
    target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${VULKAN_LIBS})
endif()

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
