#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

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
		};
	}
}

#endif /* OPENGL_TEXTURE_H */
