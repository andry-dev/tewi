#ifndef TEWI_VULKAN_INSTANCE_H
#define TEWI_VULKAN_INSTANCE_H

#include "Platform/Vulkan/Common.h"
#include "Log.h"
#include "Utils/DebugOnly.h"
#include <vector>
#include "Platform/Vulkan/ValidationLayers.h"

namespace tewi
{
	namespace Platform
	{
		namespace Vulkan
		{
			class Instance
			{
			public:
				Instance()
				{
					Expects(g_validationLayersEnabled && checkValidationLayersAvaibility(), "Validation Layers are not supported");

					// Boilerplate code
					VkApplicationInfo app = {};
					app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
					app.pApplicationName = "tewi Vulkan Loader";
					app.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
					app.pEngineName = "tewi";
					app.engineVersion = VK_MAKE_VERSION(0, 0, 1);
					app.apiVersion = VK_API_VERSION_1_0;

					VkInstanceCreateInfo info = {};
					info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
					info.pApplicationInfo = &app;

					unsigned int glfwExtensionCount = 0;
					const char** glfwExtensions;

					glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

					info.enabledExtensionCount = glfwExtensionCount;
					info.ppEnabledExtensionNames = glfwExtensions;
					info.enabledLayerCount = 0;

					DebugOnly<VkResult> instanceErrorCode = vkCreateInstance(&info, nullptr, m_instance.replace());
					Ensures(instanceErrorCode == VK_SUCCESS, "Failed to create a Vulkan instance");

					std::uint32_t extCount = 0;
					vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
					std::vector<VkExtensionProperties> extensions(extCount);
					vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensions.data());
				}

				auto getInstance() const { return m_instance; }

			private:
				VDeleter<VkInstance> m_instance{vkDestroyInstance};
			};

		}
	}
}
#endif /* TEWI_VULKAN_INSTANCE_H */
