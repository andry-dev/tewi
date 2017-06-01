cmake_minimum_required(VERSION 3.3)
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

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++latest")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Ot /GR- /GL /sdl- /LTCG")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe -Wno-pragma-once-outside-header -fno-rtti -fno-omit-frame-pointer")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -fuse-linker-plugin")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto -fuse-linker-plugin")
endif()

set(SRC
	src/IO/InputManager.cpp
	src/Physics/Collidable2D.cpp
	src/Utils/Clock.cpp
	src/Utils/TickTimer.cpp
	src/Video/Camera2D.cpp)

add_library(${PROJECT_NAME} ${SRC})

if (BUILD_SHARED_LIBS)
	message(STATUS "[tewi] Building as DLL/so")
	target_compile_definitions(${PROJECT_NAME} PUBLIC TEWI_SHARED_LIB=1)
	add_definitions(-DGLEW_BUILD)
else()
	message(STATUS "[tewi] Building as LIB/a")
	target_compile_definitions(${PROJECT_NAME} PUBLIC TEWI_STATIC_LIB=1)
	add_definitions(-DGLEW_STATIC)
endif()


message(STATUS "[tewi] Common Flags are: ${CMAKE_CXX_FLAGS}")
message(STATUS "[tewi] Debug Flags are: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "[tewi] Release Flags are: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "[tewi] Linker Flags are: ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

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

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/universal/asl/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/universal/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/universal/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/universal/stb)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 14
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set_target_properties(glfw
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${WIN32_OPENGL_LIBS}
	${VULKAN_LIBS} glm glfw asl)
