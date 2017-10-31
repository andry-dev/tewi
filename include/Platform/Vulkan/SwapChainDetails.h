#ifndef TEWI_VULKAN_SWAP_CHAIN_SUPPORT_DETAILS_H
#define TEWI_VULKAN_SWAP_CHAIN_SUPPORT_DETAILS_H

#include "Platform/Vulkan/Common.h"
#include <vector>

namespace tewi
{
    namespace Platform
    {
        namespace Vulkan
        {
            struct SwapchainSupportDetails
            {
                VkSurfaceCapabilitiesKHR capabilities;
                std::vector<VkSurfaceFormatKHR> formats;
                std::vector<VkPresentModeKHR> presentMode;
            };

            inline SwapchainSupportDetails querySwapChainSupport(VkPhysicalDevice dev, VkSurfaceKHR surface)
            {
                SwapchainSupportDetails details;

                vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface, &details.capabilities);

                std::uint32_t formatCount;
                vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &formatCount, nullptr);

                if (formatCount != 0)
                {
                    details.formats.resize(formatCount);
                    vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &formatCount, details.formats.data());
                }

                std::uint32_t presentModeCount;
                vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &presentModeCount, nullptr);

                if (presentModeCount != 0)
                {
                    details.presentMode.resize(presentModeCount);
                    vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &presentModeCount, details.presentMode.data());
                }

                return details;
            }
        }
    }
}

#endif /* TEWI_VULKAN_SWAP_CHAIN_SUPPORT_DETAILS_H */
