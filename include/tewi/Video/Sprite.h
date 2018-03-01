#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>
#include <string>

#include "tewi/Common.h"
#include "tewi/Physics/Collidable2D.h"
#include "tewi/Video/Texture.h"
#include "tewi/Video/ResourceManager.hpp"
#include "tewi/Video/TextureCache.h"
#include "tewi/Video/Renderable2D.hpp"

namespace tewi
{
    /** \brief Facility to create a basic sprite
     *
     * Use it if you don't want to mess around resources and just want a basic Sprite class.
     *
     */
    template <typename APIType>
    class TEWI_EXPORT Sprite
    {
    public:
        Sprite(const glm::vec2& pos, const std::string& path)
            : m_renderable(pos, ResourceManager<APIType, TextureCache>::getResource(path), Color(255, 255, 255, 255)),
            m_collidable(m_renderable.pos, m_renderable.texture.size)
        {
        }

        Sprite(const glm::vec2& pos, float scale, const std::string& path)
            : m_renderable(pos, ResourceManager<APIType, TextureCache>::getResource(path), Color(255, 255, 255, 255)),
            m_collidable(m_renderable.pos, m_renderable.texture.size)
        {
            m_renderable.scale = scale;
        }

        /** Returns the renderable in the form of an implicit conversion.
         *
         * Just in case you're too lazy to write \a getRenderable().
         *
         */
        operator const Renderable2D<APIType>() { return m_renderable; }

        /** Returns a pointer to the renderable via an implicit conversion.
         *
         */
        operator const Renderable2D<APIType>*() { return &m_renderable; }

        /** Returns the collidable via an implicit conversion.
         *
         * Just in case you're too lazy to write \a getCollidable().
         *
         */
        operator const Physics::Collidable2D() { return m_collidable; }

        /** Returns a pointer to the collidable via an implicit conversion.
         *
         */
        operator const Physics::Collidable2D*() { return &m_collidable; }

        /** Returns the renderable.
         *
         */
        auto getRenderable() const { return m_renderable; }

        /** Returns the collidable.
         *
         * Needed for the collision checking and basically everything that uses collidables.
         */
        auto getCollidable() const { return m_collidable; }

    protected:

        Renderable2D<APIType> m_renderable;
        Physics::Collidable2D m_collidable;
    };
}


#endif /* SPRITE_H */
