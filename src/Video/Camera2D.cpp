#include "Video/Camera2D.h"

#include <utility>

#include "glm/gtc/matrix_transform.hpp"

namespace tewi
{
	namespace Video
	{
		Camera2D::Camera2D(int screenWidth, int screenHeight)
			: m_needsMatUpdate(true),
			m_screenWidth(screenWidth),
			m_screenHeight(screenHeight),
			m_scale(1.0f),
			m_pos(0.0f, 0.0f),
			m_ortho(1.0f),
			m_cameraMat(1.0f)
		{
			m_ortho = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));
		}

		Camera2D::~Camera2D()
		{

		}

		Camera2D::Camera2D(const Camera2D& rhs)
			: m_needsMatUpdate(rhs.m_needsMatUpdate),
			m_screenWidth(rhs.m_screenWidth),
			m_screenHeight(rhs.m_screenHeight),
			m_scale(rhs.m_scale),
			m_pos(rhs.m_pos),
			m_ortho(rhs.m_ortho),
			m_cameraMat(rhs.m_cameraMat)
		{
		}

		Camera2D& Camera2D::operator=(const Camera2D& rhs)
		{
			m_needsMatUpdate = rhs.m_needsMatUpdate;
			m_screenWidth = rhs.m_screenWidth;
			m_screenHeight = rhs.m_screenHeight;
			m_scale = rhs.m_scale;
			m_pos = rhs.m_pos;
			m_ortho = rhs.m_ortho;
			m_cameraMat = rhs.m_cameraMat;
			return *this;
		}

		Camera2D::Camera2D(Camera2D&& rhs)
			: m_needsMatUpdate(std::move(rhs.m_needsMatUpdate)),
			m_screenWidth(std::move(rhs.m_screenWidth)),
			m_screenHeight(std::move(rhs.m_screenHeight)),
			m_scale(std::move(rhs.m_scale)),
			m_pos(std::move(rhs.m_pos)),
			m_ortho(std::move(rhs.m_ortho)),
			m_cameraMat(std::move(rhs.m_cameraMat))
		{
		}

		Camera2D& Camera2D::operator=(Camera2D&& rhs)
		{
			m_needsMatUpdate = std::move(rhs.m_needsMatUpdate);
			m_screenWidth = std::move(rhs.m_screenWidth);
			m_screenHeight = std::move(rhs.m_screenHeight);
			m_scale = std::move(rhs.m_scale);
			m_pos = std::move(rhs.m_pos);
			m_ortho = std::move(rhs.m_ortho);
			m_cameraMat = std::move(rhs.m_cameraMat);
			return *this;
		}

		void Camera2D::update()
		{
			if (m_needsMatUpdate)
			{
				glm::vec3 translation(-m_pos.x + m_screenWidth / 2, -m_pos.y + m_screenWidth / 2, 0.0f);
				m_cameraMat = glm::translate(m_ortho, translation);

				glm::vec3 scaling(m_scale, m_scale, 0.0f);
				m_cameraMat = glm::scale(glm::mat4(1.0f), scaling) * m_cameraMat;
				Logi("Matrix updated");

				m_needsMatUpdate = false;
			}
		}
	}
}
