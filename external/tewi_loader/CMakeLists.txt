
add_library(tewi-glloader src/gl3w.c)
target_include_directories(tewi-glloader
	SYSTEM
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:tewiGlLoader/include>
)

if (UNIX AND NOT APPLE)
    target_link_libraries(tewi-glloader PUBLIC dl)
endif()
