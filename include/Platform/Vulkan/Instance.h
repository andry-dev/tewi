#ifndef TEWI_VULKAN_INSTANCE_H
#define TEWI_VULKAN_INSTANCE_H

#include "Platform/Vulkan/Common.h"
#include "Log.h"
#include "Utils/DebugOnly.h"
#include "Platform/Vulkan/ValidationLayers.h"
#include "Platform/Vulkan/Callbacks.h"
#include "Platform/Vulkan/Devices.h"

#include <vector>

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

					if (g_validationLayersEnabled)
					{
						info.enabledLayerCount = g_validationLayerList.size();
						info.ppEnabledLayerNames = g_validationLayerList.data();
					}
					else
					{
						info.enabledLayerCount = 0;
					}

					auto exts = getExtensions();

					info.enabledExtensionCount = exts.size();
					info.ppEnabledExtensionNames = exts.data();

					DebugOnly<VkResult> instanceErrorCode = vkCreateInstance(&info, nullptr, m_instance.replace());
					Ensures(instanceErrorCode == VK_SUCCESS, "Failed to create a Vulkan instance");

					std::uint32_t extCount = 0;
					vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
					std::vector<VkExtensionProperties> extensions(extCount);
					vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensions.data());

					setupDebugCallback();
					m_devices.init(&m_instance);
				}

				auto getInstance() const { return m_instance; }

			private:
				std::vector<const char*> getExtensions()
				{
					std::vector<const char*> ext;

					unsigned int glfwExtensionCount = 0;
					const char** glfwExtensions;

					glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

					for (std::size_t i = 0; i < glfwExtensionCount; ++i)
					{
						ext.push_back(glfwExtensions[i]);
					}

					if (g_validationLayersEnabled)
					{
						ext.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
					}

					return ext;
				}

				void setupDebugCallback()
				{
					if(!g_validationLayersEnabled)
					{
						return;
					}

					VkDebugReportCallbackCreateInfoEXT info = {};
					info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
					info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT
								| VK_DEBUG_REPORT_WARNING_BIT_EXT
								| VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
					info.pfnCallback = Platform::Vulkan::debugCallback;

					VDeleter<VkDebugReportCallbackEXT> callback{m_instance, destroyDebugReportCallbackEXT};

					Expects(createDebugReportCallbackEXT(m_instance, &info, nullptr, callback.replace()) == VK_SUCCESS,
							"Failed to setup debug callback");
				}

				Device m_devices;
				VDeleter<VkInstance> m_instance{vkDestroyInstance};
			};

		}
	}
}
#endif /* TEWI_VULKAN_INSTANCE_H */
