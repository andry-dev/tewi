#ifndef EUCLIDEAN__SHAPES_H
#define EUCLIDEAN__SHAPES_H

#include "Video/Renderable2D.hpp"

namespace tewi
{
	namespace Video
	{
		class Circle : public Renderable2D
		{
		public:
			Circle(const glm::vec2& pos, const glm::vec2& size, const Color& color)
				: Renderable2D(glm::vec3(pos.x, pos.y, 0), size, color)
			{
				
			}

		};

		class Rectangle : public Renderable2D
		{
		public:
			Rectangle(const glm::vec2& pos, const glm::vec2& size, const Color& color)
				: Renderable2D(glm::vec3(pos.x, pos.y, 0), size, color)
			{
				
			}

		};
		class Triangle : public Renderable2D
		{
		public:
			Triangle(const glm::vec2& pos, const glm::vec2& size, const Color& color)
				: Renderable2D(glm::vec3(pos.x, pos.y, 0), size, color)
			{

			}

		};
	}
}


#endif /* EUCLIDEAN__SHAPES_H */
