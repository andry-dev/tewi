#ifndef COLLIDEABLE_2D_H
#define COLLIDEABLE_2D_H

#include <glm/glm.hpp>

namespace tewi
{
	namespace Physics
	{
		class Collidable2D
		{
		public:
			Collidable2D(glm::vec3& pos, glm::vec2& size);

			Collidable2D& operator=(Collidable2D& rhs);

			bool checkAABB(const Collidable2D* const other);

			bool checkRadius(const Collidable2D* const other);

		private:
			glm::vec3* m_refPos;
			glm::vec2* m_refSize;
			float m_radius;
		};
	}
}

#endif /* COLLIDEABLE_2D_H */
