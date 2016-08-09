cmake_minimum_required(VERSION 2.8)
project(tewi)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe")
endif()

set(SRC
	src/Video/Sprite.cpp
	src/Video/Shader.cpp
	src/Video/TextureCache.cpp
	src/Video/Window.cpp
	src/Utils/Clock.cpp
	src/Utils/TickTimer.cpp)

include_directories(include)

add_library(${PROJECT_NAME} ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

message(STATUS "The Flags are: ${CMAKE_CXX_FLAGS}")

if(MSVC)
	# Add SDL
	set(SDL2_LIBRARIES
		${PROJECT_SOURCE_DIR}/lib/msvc/sdl2/lib/x64/SDL2.lib
		${PROJECT_SOURCE_DIR}/lib/msvc/sdl2/lib/x64/SDL2main.lib)

	include_directories(${PROJECT_SOURCE_DIR}/lib/msvc/sdl2/include)

	# Add GLEW
	set(GLEW_LIBRARIES
		${PROJECT_SOURCE_DIR}/lib/msvc/glew/lib/Release/x64/glew32.lib)


	include_directories(${PROJECT_SOURCE_DIR}/lib/msvc/glew/include)

	set(WIN32_OPENGL_LIBS
		opengl32.lib)

else()
	INCLUDE(FindPkgConfig)

	pkg_search_module(SDL2 REQUIRED sdl2)
	pkg_search_module(GLEW REQUIRED glew)
	include_directories(${SDL2_INCLUDE_DIRS})
	include_directories(${GLEW_INCLUDE_LIBRARIES})
endif()

include_directories(lib/universal)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${WIN32_OPENGL_LIBS})
