#ifndef COLLIDEABLE_2D_H
#define COLLIDEABLE_2D_H

#include <glm/glm.hpp>

#include <vector>

namespace tewi
{
	namespace Physics
	{
		struct Collidable2D
		{
			glm::vec2* refPos;
			glm::vec2* refSize;
			float radius;
		};

		extern bool checkAABB(const Collidable2D& first, const Collidable2D& second);
		extern bool checkAABB(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup);

		extern bool checkRadius(const Collidable2D& first, const Collidable2D& second);
		extern bool checkRadius(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup);
	}
}

#endif /* COLLIDEABLE_2D_H */
