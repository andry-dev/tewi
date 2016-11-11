#ifndef TEWI_VULKAN_INSTANCE_H
#define TEWI_VULKAN_INSTANCE_H

#include "Platform/Vulkan/Common.h"
#include "Log.h"
#include "Utils/DebugOnly.h"
#include <vector>
#include <map>
#include "Platform/Vulkan/ValidationLayers.h"
#include "Platform/Vulkan/Callbacks.h"

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
					initGPUs();
				}

				auto getInstance() const { return m_instance; }

			private:
				VDeleter<VkInstance> m_instance{vkDestroyInstance};
				VkPhysicalDevice m_bestDevice = VK_NULL_HANDLE;

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

				void initGPUs()
				{
					std::uint32_t devCount = 0;
					vkEnumeratePhysicalDevices(m_instance, &devCount, nullptr);
					Expects(devCount > 0, "Can't find a Vulkan-compatible device");

					Log::debugInfo("There are " + std::to_string(devCount) + " Vulkan-compatible GPUs");

					std::vector<VkPhysicalDevice> devices(devCount);
					vkEnumeratePhysicalDevices(m_instance, &devCount, devices.data());


					std::map<std::int64_t, VkPhysicalDevice> devCandidates;

					for (const auto& dev : devices)
					{
						devCandidates[calculateDeviceScore(dev)] = dev;
					}

					m_bestDevice = devCandidates.begin()->second;

					Expects(m_bestDevice != VK_NULL_HANDLE, "Failed to find a suitable device");
				}

				bool calculateDeviceScore(VkPhysicalDevice dev)
				{
					VkPhysicalDeviceProperties devProps;
					VkPhysicalDeviceFeatures devFeatures;
					vkGetPhysicalDeviceProperties(dev, &devProps);
					vkGetPhysicalDeviceFeatures(dev, &devFeatures);

					DebugOnly<std::size_t> verMaj = VK_VERSION_MAJOR(devProps.apiVersion);
					DebugOnly<std::size_t> verMin = VK_VERSION_MINOR(devProps.apiVersion);
					DebugOnly<std::size_t> verPatch = VK_VERSION_PATCH(devProps.apiVersion);

					Log::debugInfo("dev name: " + std::string(devProps.deviceName));
					Log::debugInfo("dev api: " + std::to_string(verMaj) + "." + std::to_string(verMin));

					std::int64_t score = 0;

					if (devProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
						score += 1000; // Pretty much

					score += devProps.limits.maxImageDimension2D;
					score += devProps.limits.maxImageDimension3D;
					score += devProps.limits.maxCullDistances;
					score += devProps.limits.maxUniformBufferRange;
					score += devProps.limits.maxDrawIndirectCount;

					return score;
				}
			};

		}
	}
}
#endif /* TEWI_VULKAN_INSTANCE_H */
