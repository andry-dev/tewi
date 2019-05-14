#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "tewi/Common.h"

namespace tewi
{
    namespace Physics
    {
        struct TEWI_EXPORT Collidable2D
        {

            Collidable2D(glm::vec2& pos, glm::vec2& size);

            glm::vec2* refPos;

            glm::vec2* refSize;

            float radius;
        };

        extern TEWI_EXPORT bool checkAABB(const Collidable2D& first, const Collidable2D& second);

        extern TEWI_EXPORT bool checkAABB(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup);

        extern TEWI_EXPORT bool checkRadius(const Collidable2D& first, const Collidable2D& second);

        extern TEWI_EXPORT bool checkRadius(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup);
    }
}
