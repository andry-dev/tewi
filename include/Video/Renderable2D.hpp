#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "Video/Vertex.h"

#define TEWI_TEXTURE_DISABLE_PIXELS
#include "Video/Texture.h"
#include <array>
#include "glm/glm.hpp"
#include <type_traits>

#include <utility>

#include "Common.h"

namespace tewi
{
	/** \brief Struct that describes an object that can be rendered.
	 *
	 * The long version is: You can make your arbitrary type use this and use it with any renderer.
	 *
	 * That's because the renderers don't depend on some hierarchy OOP bullshit.
	 *
	 * Don't even try to inherit from this struct, thanks.
	 *
	 * There's a reason there is a final up there.
	 *
	 * Example:
	 *
	 * \code
	 *
	 * using namespace tewi;
	 *
	 * // Well, you really just use it in another class as a member variable
	 *
	 * class Test
	 * {
	 * public:
	 *     // Whatever you have in there
	 *
	 *
	 * private:
	 *     Renderable2D m_renderable;
	 *
	 * };
	 *
	 * // And then you just pass it around to the relevant functions
	 *
	 * batch.render(test.getRenderable()); // Assuming a BatchRenderer2D named "batch"
	 *
	 * \endcode
	 *
	 * "Why not just use inheritance?"
	 *
	 * Friendly reminder: This engine tries to stay somewhat "high performant".
	 *
	 * Inheritance leads to sloppy design which leads to cache misses; and we want to abuse that cache, right?
	 *
	 */
	template <typename APIType>
	struct TEWI_EXPORT Renderable2D final
	{
		Renderable2D(const glm::vec2& pos, const glm::vec2& size, const Color& color)
			: pos(pos), texture(), color(color), scale(1.0f)
		{
			texture.size = size;
		}

		Renderable2D(const glm::vec2& pos, Texture<APIType> texture, const Color& color)
			: pos(pos), texture(std::move(texture)), color(color), scale(1.0f)
		{

		}

		using api_type = APIType;

		glm::vec2 pos;
		Texture<APIType> texture;
		Color color;
		float scale;
	};

	//static_assert(sizeof(Renderable2D) == 28 || sizeof(Renderable2D) == 24 || sizeof(Renderable2D) >= 56, "The size of the Texture struct is not common, neither a normal value (24 | 28) nor an extremely large value (>=56, most likely due to TEWI_TEXTURE_ENABLE_PIXELS defined).");
}


#endif /* RENDERABLE_2D_H */
