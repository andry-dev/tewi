#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>
#include <string>

#include "Video/Texture.h"
#include "Video/ResourceManager.hpp"
#include "Video/TextureCache.h"

#include "Video/Renderable2D.hpp"

#include "Physics/Collidable2D.h"

namespace tewi
{
	class Sprite
	{
	public:
		Sprite(const glm::vec2& pos, const std::string& path)
			: m_renderable(pos, ResourceManager<TextureCache>::getResource(path), Color(255, 255, 255, 255)),
			m_collidable(m_renderable.pos, m_renderable.texture.size)
		{
		}

		Sprite(const glm::vec2& pos, float scale, const std::string& path)
			: m_renderable(pos, ResourceManager<TextureCache>::getResource(path), Color(255, 255, 255, 255)),
			m_collidable(m_renderable.pos, m_renderable.texture.size)
		{
			m_renderable.scale = scale;
		}

		operator const Renderable2D() { return m_renderable; }
		operator const Renderable2D*() { return &m_renderable; }

		operator const Physics::Collidable2D() { return m_collidable; }
		operator const Physics::Collidable2D*() { return &m_collidable; }

		auto getRenderable() const { return m_renderable; }
		auto getCollidable() const { return m_collidable; }

	protected:

		Renderable2D m_renderable;
		Physics::Collidable2D m_collidable;
	};
}


#endif /* SPRITE_H */
