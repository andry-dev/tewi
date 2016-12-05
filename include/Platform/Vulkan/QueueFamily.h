#ifndef TEWI_VULKAN_QUEUE_FAMILY_H
#define TEWI_VULKAN_QUEUE_FAMILY_H

#include "Platform/Vulkan/Common.h"


struct QueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;
	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

inline QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& dev)
{
	QueueFamilyIndices indices;

	std::uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, 0);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

	{
		std::size_t index = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = index;
			}

			if (indices.isComplete())
			{
				break;
			}

			++index;
		}
	}

	return indices;
}

#endif /* TEWI_VULKAN_QUEUE_FAMILY_H */
