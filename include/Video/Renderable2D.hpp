#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "Video/Vertex.h"
#include "Video/Texture.h"
#include <glm/glm.hpp>
#include <array>

namespace tewi
{
	namespace Video
	{
		class Renderable2D
		{
		public:
			Renderable2D(const glm::vec2& pos, const glm::vec2& size, const Color& color)
				: m_pos(pos), m_size(size), m_color(color)
			{

			}

			Renderable2D(const glm::vec2& pos, const glm::vec2& size, const Color& color, Texture texture)
				: m_texture(texture), m_pos(pos), m_size(size), m_color(color)
			{

			}

			Renderable2D(const glm::vec2& pos, const Color& color, Texture texture)
				: m_texture(texture), m_pos(pos), m_size(glm::vec2(texture.width, texture.height)), m_color(color)
			{

			}

			virtual ~Renderable2D()
			{

			}

			inline const auto& getSize() const noexcept { return m_size; };
			inline const auto& getPosition() const noexcept { return m_pos; }
			inline const auto& getColor() const noexcept { return m_color; }
			inline const auto& getTextureID() const noexcept { return m_texture.id; }

		protected:
			Texture m_texture;
			glm::vec2 m_pos;
			glm::vec2 m_size;
			Color m_color;
		private:
		};
	}
}


#endif /* RENDERABLE_2D_H */
