#ifndef TEWI_VULKAN_INSTANCE_H
#define TEWI_VULKAN_INSTANCE_H

#include "Platform/Vulkan/Common.h"
#include "Log.h"
#include "Utils/DebugOnly.h"
#include "Platform/Vulkan/ValidationLayers.h"
#include "Platform/Vulkan/Callbacks.h"
#include "Platform/Vulkan/LogicalDevice.h"

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

					pickPhysicalDevice();
					createLogicalDevice();

				}

				~Instance()
				{
					vkDestroyDevice(m_device, NULL);
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

				void pickPhysicalDevice()
				{
					uint32_t deviceCount = 0;
					vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

					Expects(deviceCount != 0, "failed to find GPUs with Vulkan support!");

					std::vector<VkPhysicalDevice> devices(deviceCount);
					vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

					for (const auto& device : devices)
					{
						if (isDeviceSuitable(device))
						{
							m_physicalDevice = device;
							break;
						}
					}
				}

				void createLogicalDevice()
				{
					QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

					VkDeviceQueueCreateInfo queueCreateInfo = {};
					queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
					queueCreateInfo.queueCount = 1;

					float queuePriority = 1.0f;
					queueCreateInfo.pQueuePriorities = &queuePriority;

					VkPhysicalDeviceFeatures deviceFeatures = {};

					VkDeviceCreateInfo createInfo = {};
					createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

					createInfo.pQueueCreateInfos = &queueCreateInfo;
					createInfo.queueCreateInfoCount = 1;

					createInfo.pEnabledFeatures = &deviceFeatures;

					createInfo.enabledExtensionCount = 0;
					
					if (g_validationLayersEnabled)
					{
						createInfo.enabledLayerCount = g_validationLayerList.size();
						createInfo.ppEnabledLayerNames = g_validationLayerList.data();
					}
					else
					{
						createInfo.enabledLayerCount = 0;
					}

					Ensures(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) == VK_SUCCESS, "Failed to create logical device");

					vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_queue);
				}

				bool isDeviceSuitable(VkPhysicalDevice device)
				{
					QueueFamilyIndices indices = findQueueFamilies(device);

					return indices.isComplete();
				}

				QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
				{
					QueueFamilyIndices indices;

					uint32_t queueFamilyCount = 0;
					vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

					std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
					vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

					int i = 0;
					for (const auto& queueFamily : queueFamilies)
					{
						if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
						{
							indices.graphicsFamily = i;
						}

						if (indices.isComplete()) {
							break;
						}

						i++;
					}

					return indices;
				}

				VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
				
				// For some bullshit reasons the destructor for VDeleter won't be called here
				VkDevice m_device;
				VDeleter<VkInstance> m_instance{vkDestroyInstance};
				VDeleter<VkSurfaceKHR> surface{m_instance, vkDestroySurfaceKHR};
				VkQueue m_queue;
			};
		}
	}
}
#endif /* TEWI_VULKAN_INSTANCE_H */
