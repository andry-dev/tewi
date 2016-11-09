#ifndef TEWI_VULKAN_VALIDATION_LAYERS_H
#define TEWI_VULKAN_VALIDATION_LAYERS_H

#include "Platform/Vulkan/Common.h"

#include <vector>
#include <cstdint>
#include <cstring>

namespace tewi
{
	namespace Platform
	{
		namespace Vulkan
		{
			const std::vector<const char*> g_enabledValidationLayers =
			{
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
				vkEnumerateInstanceLayerProperties(&layerCount, avaibleLayers.data());

				for (const auto& layer : g_enabledValidationLayers)
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
		}
	}
}
#endif /* TEWI_VULKAN_VALIDATION_LAYERS_H */
