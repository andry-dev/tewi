#pragma once

#include <vector>

#include "glm/glm.hpp"

#include <cstdint>

namespace tewi
{

	/** \brief Basic texture struct.
	 *
	 * And worst class ever!
	 *
	 * Define "TEWI_TEXTURE_ENABLE_PIXELS" to enable the saving of pixels in the texture, increasing memory usage (most likely cache by a factor of two) but enabling pixel-perfect collision detection (ndr: Not even implemented yet).
	 *
	 * TODO: Actually fix this that it's unacceptable.
	 *
	 */
	template <typename APINum>
	struct Texture
	{
		std::uint32_t id;
		glm::vec2 size;

#ifdef TEWI_TEXTURE_ENABLE_PIXELS
		std::vector<std::uint8_t> pixels;
#endif /* TEWI_TEXTURE_DISABLE_PIXELS */
	};
}