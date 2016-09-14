#include "Physics/Collidable2D.h"

namespace tewi
{
	namespace Physics
	{
		Collidable2D::Collidable2D(glm::vec3& pos, glm::vec2& size)
			: m_refPos(&pos), m_refSize(&size), m_radius(pos.x / 2.0f)
		{

		}

		Collidable2D& Collidable2D::operator=(Collidable2D& rhs)
		{
			if (this != &rhs)
			{
				m_refPos = rhs.m_refPos;
				m_refSize = rhs.m_refSize;
				m_radius = rhs.m_radius;
			}
			return *this;
		}

		bool Collidable2D::checkAABB(const Collidable2D* const other)
		{
			return (m_refPos->x < other->m_refPos->x + other->m_refSize->x &&
					m_refPos->x + m_refSize->x > other->m_refPos->x &&
					m_refPos->y < other->m_refPos->y + other->m_refSize->y &&
					m_refPos->y + m_refSize->y > other->m_refPos->y);
		}

		bool Collidable2D::checkRadius(const Collidable2D* const other)
		{
			float distance_x = (m_refPos->x + m_radius) - (other->m_refPos->x + other->m_radius);
			float distance_y = (m_refPos->y + m_radius) - (other->m_refPos->y + other->m_radius);

			float distance = std::sqrt(distance_x * distance_x + distance_y * distance_y);

			return distance < m_radius + other->m_radius;
		}
	}
}
