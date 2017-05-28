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

		/** \brief Null Renderer Tag
		 *
		 * Struct used for API switch.
		 *
		 * This in particular is used for server stuff where you don't want a
		 * window.
		 *
		 */
		struct TEWI_EXPORT NullRendererTag
		{
			enum { value = 2 };
		};
	}
}
