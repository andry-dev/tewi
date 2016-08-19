#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Video/Texture.h"
#include "Video/ResourceManager.hpp"
#include "Video/TextureCache.h"

#include "Video/Renderable2D.hpp"

namespace tewi
{
	namespace Video
	{
		class Sprite : public Renderable2D
		{
		public:
			Sprite(const glm::vec2& pos, const glm::vec2& size, const std::string& path)
				: Renderable2D(glm::vec3(pos.x, pos.y, 0), size, Color(255, 255, 255, 255), ResourceManager<TextureCache>::getResource(path))
			{
			}

			~Sprite()
			{
				
			}
		private:
		};
	}
}


#endif /* SPRITE_H */
