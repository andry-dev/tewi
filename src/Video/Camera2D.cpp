#include "tewi/Video/Camera2D.h"

#include <utility>

#include "glm/gtc/matrix_transform.hpp"
#include "tewi/Utils/Types.h"

namespace tewi
{
    Camera2D::Camera2D(int screenWidth, int screenHeight)
        : m_needsMatUpdate(true)
        , m_screenWidth(screenWidth)
        , m_screenHeight(screenHeight)
        , m_scale(1.0f)
        , m_pos(0.0f, 0.0f)
        , m_ortho(1.0f)
        , m_cameraMat(1.0f)
    {
        m_ortho = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f,
                             static_cast<float>(screenHeight));
    }

    void Camera2D::update()
    {
        if (m_needsMatUpdate)
        {
            glm::vec3 translation(-m_pos.x + m_screenWidth / 2,
                                  -m_pos.y + m_screenWidth / 2, 0.0f);
            m_cameraMat = glm::translate(m_ortho, translation);

            glm::vec3 scaling(m_scale, m_scale, 0.0f);
            m_cameraMat = glm::scale(glm::mat4(1.0f), scaling) * m_cameraMat;
            Log::debugInfo("Matrix updated");

            m_needsMatUpdate = false;
        }
    }

    // TODO: This should be changed, output parameters are bad
    void Camera2D::getWorldCoordsFromScreenCoords(glm::vec2& coords)
    {
        coords.y = m_screenHeight - coords.y;
        coords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
        coords /= m_scale;
        coords += m_pos;
    }
} // namespace tewi
