#ifndef TEWI_COLLIDEABLE_2D_H
#define TEWI_COLLIDEABLE_2D_H

#include <glm/glm.hpp>

#include <vector>

#include "Common.h"

namespace tewi
{
	/** Namespace for physics.
	 *
	 */
	namespace Physics
	{

		/** \brief Struct that describes an object that can collide with other collidables.
		 *
		 * It's basically used in whatever class you want to "save" just the position, size and radius of an object and to store it in a common class.
		 *
		 * I'm using pointers because there's no need to copy floats.
		 *
		 * **Examples:**
		 *
		 * \code
		 *
		 * using namespace tewi;
		 *
		 * // Suppose we have a class that uses this collidable to check collisions:
		 *
		 * class Projectile
		 * {
		 * public:
		 *     Projectile( ... );
		 *
		 *     // Let's just skip ahead.
		 *
		 *     auto getCollidable() { return m_collidable; }
		 *
		 * private:
		 *
		 *     Renderable2D m_renderable; // Or whatever.
		 *
		 *     Collidable2D m_collidable;
		 * };
		 *
		 * // And instantiates it:
		 *
		 * Projectile::Projectile( ... )
		 * {
		 *     m_collidable.refPos = &m_renderable.pos;
		 *     m_collidable.refSize = &m_renderable.texture.size;
		 *
		 *     // Or whatever you use to store the position
		 * }
		 *
		 * // Then we can simply check collisions by invoking the appropriate functions:
		 *
		 * {
		 *     Projectile prj( ... );
		 *     Projectile prj2( ... );
		 *
		 *
		 *     if (checkAABB(prj.getCollidable(), prj2.getCollidable()))
		 *     {
		 *         // Collision happened
		 *     }
		 *     else
		 *     {
		 *         // Normal stuff
		 *     }
		 * }
		 *
		 * \endcode
		 *
		 * The advantage is that you don't need inheritance, so the "dependency" for our physics engine is reduced (because asking for an entire "Sprite" object is too much and it can force you to just strictly follow this engine).
		 *
		 * AND, we're passing small objects (two pointers + 4 bytes), so we shouldn't get much cache misses (even if there are pointers and we need to dereference them...).
		 *
		 */
		struct TEWI_EXPORT Collidable2D
		{

			/** Constructor for the class.
			 *
			 */
			Collidable2D(glm::vec2& pos, glm::vec2& size);

			/** Pointer to the position of the object.
			 *
			 */
			glm::vec2* refPos;

			/** Pointer to the size of the object.
			 *
			 */
			glm::vec2* refSize;

			/** Radius of the object.
			 *
			 */
			float radius;
		};

		/** Checks AABB collision between single collidables.
		 *
		 */
		extern TEWI_EXPORT bool checkAABB(const Collidable2D& first, const Collidable2D& second);

		/** Checks AABB collision between a vector of collidables.
		 *
		 * \return false if **ANY** of the elements in the first vector **didn't collide** with **ANY** element of the second vector.
		 * \return true if **ALL** the elements in the first vector **collided** with **ALL** the elements in the second vector.
		 *
		 */
		extern TEWI_EXPORT bool checkAABB(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup);

		/** Checks collision via radius between single collidables.
		 *
		 */
		extern TEWI_EXPORT bool checkRadius(const Collidable2D& first, const Collidable2D& second);

		/** Checks collision via radius between a vector of collidables.
		 *
		 * \return false if **ANY** of the elements in the first vector **didn't collide** with **ANY** element of the second vector.
		 * \return true if **ALL** the elements in the first vector **collided** with **ALL** the elements in the second vector.
		 *
		 */
		extern TEWI_EXPORT bool checkRadius(const std::vector<Collidable2D>& firstGroup, const std::vector<Collidable2D>& secondGroup);
	}
}

#endif /* TEWI_COLLIDEABLE_2D_H */
