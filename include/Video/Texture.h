#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <vector>

#include <cstdint>

namespace tewi
{
	namespace Video
	{
		struct Texture
		{
			std::uint32_t id;
			int width;
			int height;

			std::vector<std::uint8_t> pixels;
		};
	}
}

#endif /* OPENGL_TEXTURE_H */
