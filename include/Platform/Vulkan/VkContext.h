#ifndef TEWI_VULKAN_CONTEXT_H
#define TEWI_VULKAN_CONTEXT_H

#include "Video/API/Context.h"

#include "Platform/Vulkan/Instance.h"

#include "Platform/Vulkan/Common.h"

namespace tewi
{
	namespace API
	{
		/** \brief Vulkan Context.
		 *
		 *
		 * Tries to initialize Vulkan.
		 *
		 * You shouldn't be reading this, by the way.
		 *
		 *
		 * **Internal use only.**
		 *
		 */
		template<>
		class Context<API_TYPE::VULKAN>
		{
		public:
			Context()
			{
			}

			void setup()
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			}

			void postInit()
			{
				m_instance.initVulkan();
			}

			void preDraw()
			{

			}

			void postDraw()
			{

			}

			void createSurface(GLFWwindow* window)
			{
				m_instance.createSurface(window);
			}

			const char* getAPIVersion()
			{
				return "Vulkan";
			}

		private:

			Platform::Vulkan::Instance m_instance;
		};

		using VkContext = Context<API_TYPE::VULKAN>;
	}
}

#endif /* TEWI_VULKAN_CONTEXT_H */
