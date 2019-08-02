
add_library(tewi-glloader src/gl3w.c)
target_include_directories(tewi-glloader
	SYSTEM
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:tewiGlLoader/include>
)
