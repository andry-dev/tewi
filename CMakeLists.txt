cmake_minimum_required(VERSION 2.8)
project(tewi)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/universal/glfw)
include_directories(lib/universal/glfw)

add_subdirectory(lib/universal/glm)
include_directories(lib/universal/glm)

add_subdirectory(doc)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe -flto")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto=8")
endif()

set(SRC
	src/IO/InputManager.cpp
	src/Physics/Collidable2D.cpp
	src/Utils/Clock.cpp
	src/Utils/TickTimer.cpp
	src/Video/Camera2D.cpp
	src/Video/Shader.cpp
	src/Video/TextureCache.cpp)

include_directories(include)

add_library(${PROJECT_NAME} ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

message(STATUS "The Flags are: ${CMAKE_CXX_FLAGS}")

if(MSVC)
	# Add GLEW
	set(GLEW_LIBRARIES
		${PROJECT_SOURCE_DIR}/lib/msvc/glew/lib/Release/x64/glew32.lib)

	include_directories(${PROJECT_SOURCE_DIR}/lib/msvc/glew/include)

	include_directories(${PROJECT_SOURCE_DIR}/lib/msvc/vulkan/include)

	set(VULKAN_LIBS
		${PROJECT_SOURCE_DIR}/lib/msvc/vulkan/lib/vulkan-1.lib)

	set(WIN32_OPENGL_LIBS
		opengl32.lib)

else()
	INCLUDE(FindPkgConfig)

	pkg_search_module(GLEW REQUIRED glew)
	include_directories(${GLEW_INCLUDE_DIRS})

	set(VULKAN_LIBS
		vulkan)
endif()

include_directories(lib/universal)

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${WIN32_OPENGL_LIBS} ${VULKAN_LIBS} glm glfw)
