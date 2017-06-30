cmake_minimum_required(VERSION 3.6)
project(tewi)

option(TEWI_BUILD_TESTS "Build tewi's tests" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/universal/glfw)
add_subdirectory(lib/universal/asl)
add_subdirectory(lib/universal/glm)
add_subdirectory(doc)

if (TEWI_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()


set(SRC
	src/IO/InputManager.cpp
	src/Physics/Collidable2D.cpp
	src/Utils/Clock.cpp
	src/Utils/TickTimer.cpp
	src/Video/Camera2D.cpp)


set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_library(${PROJECT_NAME} ${SRC})

if(MSVC)
	# Common
	target_compile_options(${PROJECT_NAME}
		PRIVATE
		/W4 /std:c++latest)

	# Release
	# target_compile_options(${PROJECT_NAME}
	# 	PRIVATE
	# 	$<$<CONFIG:RELEASE>:/Ob2 /Ot /GR- /GL /sdl- /LTCG)
else()
	# Common
	target_compile_options(${PROJECT_NAME}
		PRIVATE
		-Wall -pipe -Wno-pragma-once-outside-header -fno-rtti -fno-omit-frame-pointer)

	# Release
	target_compile_options(${PROJECT_NAME}
		PRIVATE
		$<$<CONFIG:RELEASE>:-O3>)
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

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON)

if(WIN32)
	# Add GLEW
	set(GLEW_LIBRARIES
		${PROJECT_SOURCE_DIR}/lib/msvc/glew/lib/Release/x64/glew32.lib)

	target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/msvc/glew/include)
	target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/msvc/vulkan/include)

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
	${GLEW_LIBRARIES}
	${WIN32_OPENGL_LIBS}
	${VULKAN_LIBS}
	glm
	glfw
	asl)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
if(CLANG_TIDY_EXE)
	message(STATUS "[tewi] clang-tidy found: ${CLANG_TIDY_EXE}")
	set(EXECUTE_CLANG_TIDY "${CLANG_TIDY_EXE}"
		"-header-filter=\"${PROJECT_SOURCE_DIR}/include/*\" -checks=*,-clang-analyzer-alpha.*,-cppcoreguidelines-pro-type-union-access")
	set_target_properties(${PROJECT_NAME}
		PROPERTIES
		CXX_CLANG_TIDY "${EXECUTE_CLANG_TIDY}")
endif()
