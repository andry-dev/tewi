#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "Video/Vertex.h"
#include "Video/Texture.h"
#include <glm/glm.hpp>
#include <array>

namespace tewi
{
	// Don't you ever try to inherit from this class
	struct Renderable2D final
	{
		Renderable2D(const glm::vec2& pos, const glm::vec2& size, const Color& color)
			: pos(pos), texture(), color(color), scale(1.0f)
		{
			texture.size = size;
		}

		Renderable2D(const glm::vec2& pos, Texture texture, const Color& color)
			: pos(pos), texture(texture), color(color), scale(1.0f)
		{

		}

		glm::vec2 pos;
		Texture texture;
		Color color;
		float scale;
	};
}


#endif /* RENDERABLE_2D_H */
