cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0069 NEW)
project(tewi)

include(CheckIPOSupported)

option(TEWI_BUILD_TESTS "Build tewi's tests" OFF)
option(TEWI_ENABLE_VULKAN "Enable Vulkan support" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/universal/glfw)
add_subdirectory(lib/universal/asl)
add_subdirectory(lib/universal/glm)
add_subdirectory(doc)


set(SRC
	src/IO/InputManager.cpp
	src/Physics/Collidable2D.cpp
	src/Utils/Clock.cpp
	src/Utils/TickTimer.cpp
	src/Video/Camera2D.cpp)

set(IN_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include/tewi)

set(PUBLIC_HEADERS
    ${IN_INCLUDE_DIR}/Common.h
    ${IN_INCLUDE_DIR}/GameCommon.hpp

    # Events
    ${IN_INCLUDE_DIR}/EventSystem/Event.h
    ${IN_INCLUDE_DIR}/EventSystem/EventType.h

    # Input/Output
    ${IN_INCLUDE_DIR}/IO/BasicIO.h
    ${IN_INCLUDE_DIR}/IO/InputManager.h

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
    # Null Renderer
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/BatchRenderer2D.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/Context.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/Device.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/GameCommon.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/Instance.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/Shader.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/Swapchain.hpp
    ${IN_INCLUDE_DIR}/Platform/NullRenderer/Window.hpp

    # OpenGL
    ${IN_INCLUDE_DIR}/Platform/OpenGL/BatchRenderer2D.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/Context.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/Device.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/IndexBuffer.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/Instance.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/Shader.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/Swapchain.hpp
    ${IN_INCLUDE_DIR}/Platform/OpenGL/TextureCache.hpp

    # Vulkan
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Callbacks.h
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Common.h
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Context.hpp
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Device.hpp
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Instance.hpp
    ${IN_INCLUDE_DIR}/Platform/Vulkan/QueueFamily.h
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Shader.hpp
    ${IN_INCLUDE_DIR}/Platform/Vulkan/Swapchain.hpp
    ${IN_INCLUDE_DIR}/Platform/Vulkan/SwapchainDetails.h
    ${IN_INCLUDE_DIR}/Platform/Vulkan/ValidationLayers.h
    ${IN_INCLUDE_DIR}/Utils/GLFWCallbacks.h)

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
        -Wall -Wextra -pedantic -pipe -Wno-pragma-once-outside-header
        -Weffc++ -Wno-c++98-compat -Wno-unused-const-variable
        -Wno-missing-prototypes -fno-rtti)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME}
            PRIVATE
            -Weverything)
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
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)

check_ipo_supported(RESULT lto_supported)
if (lto_supported)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()


if (BUILD_SHARED_LIBS)
	message(STATUS "[tewi] Building as DLL/so")
	target_compile_definitions(${PROJECT_NAME} PUBLIC TEWI_SHARED_LIB=1)
	add_definitions(-DGLEW_BUILD)
else()
	message(STATUS "[tewi] Building as LIB/a")
	target_compile_definitions(${PROJECT_NAME} PUBLIC TEWI_STATIC_LIB=1)
	add_definitions(-DGLEW_STATIC)
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

	target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/msvc/glew/include)
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
	include(FindPkgConfig)

	pkg_search_module(GLEW REQUIRED glew)
	target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})

	set(VULKAN_LIBS
		vulkan)
endif()

target_include_directories(${PROJECT_NAME}
	PUBLIC
	${PROJECT_SOURCE_DIR}/lib/universal/asl/include
	${PROJECT_SOURCE_DIR}/lib/universal/glfw/include
	${PROJECT_SOURCE_DIR}/lib/universal/glm
	${PROJECT_SOURCE_DIR}/lib/universal/stb
	${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
	${GLEW_LIBRARIES}
	${WIN32_OPENGL_LIBS}
	glm
	glfw
	asl)

if (TEWI_ENABLE_VULKAN)
    target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${VULKAN_LIBS})
endif()

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
if(CLANG_TIDY_EXE)
	message(STATUS "[tewi] clang-tidy found: ${CLANG_TIDY_EXE}")
    file(GLOB_RECURSE
        ALL_SOURCES
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/include/*.hpp
        ${PROJECT_SOURCE_DIR}/include/*.hxx
        ${PROJECT_SOURCE_DIR}/src/*.cpp)
	add_custom_target(clang-tidy
        COMMAND ${CLANG_TIDY_EXE}
        ${ALL_SOURCES}
        -p ${CMAKE_BINARY_DIR}
        -header-filter=${PROJECT_SOURCE_DIR}/include/*
        -checks=*,-clang-analyzer-alpha.*,-cppcoreguidelines-pro-type-union-access
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Checking code with clang-tidy" VERBATIM)
endif()

if (TEWI_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
