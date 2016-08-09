#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Video/Texture.h"

namespace tewi
{
	namespace Video
	{
		class Sprite
		{
		public:
			Sprite(float x, float y, float w, float h, const std::string& path);
			~Sprite();
			
			void draw();
		private:


			float m_xpos = 0;
			float m_ypos = 0;
			float m_width = 0;
			float m_height = 0;

			std::uint32_t m_VBOID = 0;
			Texture m_texture;
		};
	}
}


#endif /* SPRITE_H */
