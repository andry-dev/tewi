#ifndef TEWI_VULKAN_CONTEXT_H
#define TEWI_VULKAN_CONTEXT_H

#include "Video/API/Context.h"

#include "Platform/Vulkan/Instance.h"

namespace tewi
{
	namespace Video
	{
		namespace API
		{
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
					
				}

				void preDraw()
				{

				}

				void postDraw()
				{

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
}

#endif /* TEWI_VULKAN_CONTEXT_H */
