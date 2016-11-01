#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <vector>

#include <glm/glm.hpp>

#include <cstdint>

namespace tewi
{
	namespace Video
	{
		struct Texture
		{
			std::uint32_t id;
			glm::vec2 size;

			std::vector<std::uint8_t> pixels;
		};
	}
}

#endif /* OPENGL_TEXTURE_H */
