#include "Physics/Collidable2D.h"

namespace tewi
{
	namespace Physics
	{
		bool checkAABB(const Collidable2D& first, const Collidable2D& second)
		{
			return ((first.refPos->x < second.refPos->x + second.refSize->x) &
					(first.refPos->x + first.refSize->x > second.refPos->x) &
					(first.refPos->y < second.refPos->y + second.refSize->y) &
					(first.refPos->y + first.refSize->y > second.refPos->y));
		}

		bool checkAABB(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup)
		{
			bool test = true;
			for (const auto& first : firstGroup)
			{
				for (const auto& second : secondGroup)
				{
					if (!((first.refPos->x < second.refPos->x + second.refSize->x) &
						(first.refPos->x + first.refSize->x > second.refPos->x) &
						(first.refPos->y < second.refPos->y + second.refSize->y) &
						(first.refPos->y + first.refSize->y > second.refPos->y)))
					{
						test = false;
					}
				}
			}

			return test;
		}

		bool checkRadius(const Collidable2D& first, const Collidable2D& second)
		{
			float distance_x = (first.refPos->x + first.radius) - (second.refPos->x + second.radius);
			float distance_y = (first.refPos->y + first.radius) - (second.refPos->y + second.radius);

			float distance = (distance_x * distance_x + distance_y * distance_y);

			return distance < (first.radius * first.radius + second.radius * second.radius);
		}

		bool checkRadius(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup)
		{
			bool test = true;
			for (const auto& first : firstGroup)
			{
				for (const auto& second : secondGroup)
				{
					float distance_x = (first.refPos->x + first.radius) - (second.refPos->x + second.radius);
					float distance_y = (first.refPos->y + first.radius) - (second.refPos->y + second.radius);

					float distance = (distance_x * distance_x + distance_y * distance_y);

					if (!(distance < (first.radius * first.radius + second.radius * second.radius)))
					{
						test = false;
					}
				}
			}

			return test;
		}
	}
}
