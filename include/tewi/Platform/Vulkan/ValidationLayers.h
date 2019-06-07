#pragma once

#ifdef TEWI_ENABLE_VULKAN

#include "Platform/Vulkan/Common.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

namespace tewi
{
    namespace Platform
    {
        namespace Vulkan
        {
            const std::array<const char*, 1> g_validationLayerList = {
                "VK_LAYER_LUNARG_standard_validation"
            };

#ifdef NDEBUG
            constexpr bool g_validationLayersEnabled = false;
#else
            constexpr bool g_validationLayersEnabled = true;
#endif

            inline bool checkValidationLayersAvaibility()
            {
                std::uint32_t layerCount;
                vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

                std::vector<VkLayerProperties> avaibleLayers(layerCount);
                vkEnumerateInstanceLayerProperties(&layerCount,
                                                   avaibleLayers.data());

                for (const auto& layer : g_validationLayerList)
                {
                    bool layerFound = false;

                    for (const auto& layerProp : avaibleLayers)
                    {
                        if (std::strcmp(layer, layerProp.layerName) == 0)
                        {
                            layerFound = true;
                            break;
                        }
                    }

                    if (!layerFound)
                        return false;
                }

                return true;
            }
        } // namespace Vulkan
    }     // namespace Platform
} // namespace tewi

#endif /* TEWI_ENABLE_VULKAN */
