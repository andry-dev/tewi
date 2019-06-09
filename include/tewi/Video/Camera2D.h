#pragma once

#include <string>

#include "glm/glm.hpp"
#include "tewi/Common.h"
#include "tewi/Utils/Log.h"

namespace tewi
{
    class TEWI_EXPORT Camera2D
    {
    public:
        Camera2D(int screenWidth, int screenHeight);
        ~Camera2D() = default;

        Camera2D(const Camera2D& rhs) = default;
        Camera2D& operator=(const Camera2D& rhs) = default;

        Camera2D(Camera2D&& rhs) = default;
        Camera2D& operator=(Camera2D&& rhs) = default;

        void update();

        void getWorldCoordsFromScreenCoords(glm::vec2& coords);

        inline auto getScale() const
        {
            return m_scale;
        }
        inline auto getPosition() const
        {
            return m_pos;
        }
        inline auto getMatrix() const
        {
            return m_cameraMat;
        }

        inline void setScale(float scale)
        {
            m_scale = scale;
            m_needsMatUpdate = true;
        }

        inline void setPosition(const glm::vec2& pos)
        {
            m_pos = pos;
            m_needsMatUpdate = true;
        }

    private:
        bool m_needsMatUpdate;
        int m_screenWidth;
        int m_screenHeight;

        float m_scale;
        glm::vec2 m_pos;
        glm::mat4 m_ortho;
        glm::mat4 m_cameraMat;
    };
} // namespace tewi
