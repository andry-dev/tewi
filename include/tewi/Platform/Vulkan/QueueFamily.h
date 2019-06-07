#pragma once

#ifdef TEWI_ENABLE_VULKAN

#include "Platform/Vulkan/Common.h"

namespace tewi
{
    namespace Platform
    {
        namespace Vulkan
        {
            struct QueueFamilyIndices
            {
                int graphicsFamily = -1;
                int presentFamily = -1;
                bool isComplete()
                {
                    return graphicsFamily >= 0 && presentFamily >= 0;
                }
            };

            inline QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev,
                                                        VkSurfaceKHR surface)
            {
                QueueFamilyIndices indices;

                std::uint32_t queueFamilyCount = 0;
                vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount,
                                                         0);

                std::vector<VkQueueFamilyProperties> queueFamilies(
                    queueFamilyCount);
                vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount,
                                                         queueFamilies.data());

                {
                    int index = 0;
                    for (const auto& queueFamily : queueFamilies)
                    {

                        if ((queueFamily.queueCount > 0) &&
                            (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT))
                        {
                            indices.graphicsFamily = index;
                        }

                        VkBool32 presentationSupport = false;
                        vkGetPhysicalDeviceSurfaceSupportKHR(
                            dev, index, surface, &presentationSupport);

                        if ((queueFamily.queueCount > 0) && presentationSupport)
                        {
                            indices.presentFamily = index;
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
        } // namespace Vulkan
    }     // namespace Platform

} // namespace tewi

#endif /* TEWI_ENABLE_VULKAN */
