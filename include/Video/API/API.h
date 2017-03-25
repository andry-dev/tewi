#pragma once

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
		struct OpenGLTag
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
		struct VulkanTag
		{
			enum { value = 1 };
		};
	}
}
