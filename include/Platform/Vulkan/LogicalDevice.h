#ifndef TEWI_VULKAN_LOGICAL_DEVICE_H
#define TEWI_VULKAN_LOGICAL_DEVICE_H

#include "Platform/Vulkan/Common.h"
#include "Platform/Vulkan/PhysicalDevices.h"

#include "Platform/Vulkan/ValidationLayers.h"

// TODO: This class is completely useless
// PLEASE REMOVE.
namespace tewi
{
	namespace Platform
	{
		namespace Vulkan
		{
			class LogicalDevice
			{
				public:
					void init(VDeleter<VkInstance>* instance)
					{
						m_physicalDevices.init(instance);
					}

				private:
					void createLogicalDevice()
					{
						auto bestDevice = m_physicalDevices.getBestDevice();
						auto indices = findQueueFamilies(bestDevice);

						VkDeviceQueueCreateInfo info = {};
						info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
						info.queueFamilyIndex = indices.graphicsFamily;
						info.queueCount = 1;

						float queuePriority = 1.0f;
						info.pQueuePriorities = &queuePriority;

						VkPhysicalDeviceFeatures devFeatures = {};

						VkDeviceCreateInfo devInfo = {};
						devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
						devInfo.pQueueCreateInfos = &info;
						devInfo.queueCreateInfoCount = 1;
						devInfo.pEnabledFeatures = &devFeatures;
						devInfo.enabledExtensionCount = 0;

						if (g_validationLayersEnabled)
						{
							devInfo.enabledLayerCount = g_validationLayerList.size();
							devInfo.ppEnabledLayerNames = g_validationLayerList.data();
						}
						else
						{
							devInfo.enabledLayerCount = 0;
						}

						DebugOnly<VkResult> res = vkCreateDevice(bestDevice, &devInfo, nullptr, m_logicalDevice.replace());
						Expects(res == VK_SUCCESS, "Can't create Vulkan logical device");


					}

					VDeleter<VkDevice> m_logicalDevice{vkDestroyDevice};
					PhysicalDevices m_physicalDevices;
			};
		}

	}
}
#endif /* TEWI_VULKAN_LOGICAL_DEVICE_H */
