#pragma once

#include <array>
#include <type_traits>
#include <utility>

#include "tewi/Common.h"
#include "tewi/Video/Texture.h"
#include "tewi/Video/Vertex.h"

#include "glm/glm.hpp"

namespace tewi
{
    template <typename APIType>
    struct TEWI_EXPORT Renderable2D final
    {
        Renderable2D(const glm::vec2& pos, const glm::vec2& size, const Color& color)
            : pos(pos), texture(), color(color), scale(1.0f)
        {
            texture.size = size;
        }

        Renderable2D(const glm::vec2& pos, Texture<APIType> texture, const Color& color)
            : pos(pos), texture(std::move(texture)), color(color), scale(1.0f)
        {

        }

        using api_type = APIType;

        glm::vec2 pos;
        Texture<APIType> texture;
        Color color;
        float scale;
    };
}
