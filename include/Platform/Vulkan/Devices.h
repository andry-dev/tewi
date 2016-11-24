#ifndef TEWI_VULKAN_LOGICAL_DEVICE_H
#define TEWI_VULKAN_LOGICAL_DEVICE_H

#include "Platform/Vulkan/Common.h"
#include "Platform/Vulkan/PhysicalDevices.h"

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
						auto indices = findQueueFamilies(m_physicalDevices.getBestDevice());

						VkDeviceQueueCreateInfo info = {};
						info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
						info.queueFamilyIndex = indices.graphicsFamily;
						info.queueCount = 1;

						float queuePriority = 1.0f;
						info.pQueuePriorities = &queuePriority;
					}

					VDeleter<VkDevice> m_logicalDevice{vkDestroyDevice};
					PhysicalDevices m_physicalDevices;
			};
		}

	}
}
#endif /* TEWI_VULKAN_LOGICAL_DEVICE_H */
