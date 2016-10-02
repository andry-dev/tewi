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

#include "Physics/Collidable2D.h"

namespace tewi
{
	namespace Video
	{
		class Sprite : public Renderable2D, public Physics::Collidable2D
		{
		public:
			Sprite(const glm::vec2& pos, const std::string& path)
				: Renderable2D(pos, Color(255, 255, 255, 255), ResourceManager<TextureCache>::getResource(path)),
				Collidable2D(Renderable2D::m_pos, Renderable2D::m_size)
			{
			}

			Sprite(const glm::vec2& pos, const glm::vec2& size, const std::string& path)
				: Renderable2D(pos, size, Color(255, 255, 255, 255), ResourceManager<TextureCache>::getResource(path)),
				Collidable2D(Renderable2D::m_pos, Renderable2D::m_size)
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
