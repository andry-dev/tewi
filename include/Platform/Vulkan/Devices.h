#ifndef TEWI_VULKAN_DEVICES_H
#define TEWI_VULKAN_DEVICES_H

#include "Platform/Vulkan/Common.h"
#include "Log.h"
#include "Utils/DebugOnly.h"

#include <vector>
#include <map>

namespace tewi
{
	namespace Platform
	{
		namespace Vulkan
		{
			class Device
			{
			public:
				Device()
				{

				}

				void init(VDeleter<VkInstance>* instance)
				{
					m_instance = instance;
					findGPUs();
				}

				auto getDevices() const { return m_devices; }

			private:
				void findGPUs()
				{
					std::uint32_t devCount = 0;
					vkEnumeratePhysicalDevices(*m_instance, &devCount, nullptr);
					Expects(devCount > 0, "Can't find a Vulkan-compatible device");

					Log::debugInfo("There are " + std::to_string(devCount) + " Vulkan-compatible GPUs");

					m_devices.reserve(devCount);
					vkEnumeratePhysicalDevices(*m_instance, &devCount, m_devices.data());

					for (const auto& dev : m_devices)
					{
						m_candidateDevices[calculateDeviceScore(dev)] = dev;
					}

					m_bestDevice = m_candidateDevices.begin()->second;

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

				VkPhysicalDevice m_bestDevice = VK_NULL_HANDLE;
				std::vector<VkPhysicalDevice> m_devices;
				std::map<std::int64_t, VkPhysicalDevice> m_candidateDevices;
				VDeleter<VkInstance>* m_instance;
			};
		}
	}
}

#endif /* TEWI_VULKAN_DEVICES_H */
