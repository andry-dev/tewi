#pragma once

#include "Common.h"

namespace tewi
{
	namespace API
	{
		/** \brief OpenGL Tag
		 *
		 * Struct used for API switch.
		 *
		 * The "value" is for future use.
		 *
		 */
		struct TEWI_EXPORT OpenGLTag
		{
			enum { value = 1 };
		};

		/** \brief Vulkan Tag
		 *
		 * Struct used for API switch.
		 *
		 * The "value" is for future use.
		 *
		 */
		struct TEWI_EXPORT VulkanTag
		{
			enum { value = 1 };
		};
	}
}
