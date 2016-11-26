#ifndef TEWI_VULKAN_PHYSICAL_DEVICES_H
#define TEWI_VULKAN_PHYSICAL_DEVICES_H

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
			struct QueueFamilyIndices
			{
				int graphicsFamily = -1;
				bool isComplete()
				{
					return graphicsFamily >= 0;
				}
			};

			inline QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev)
			{
				QueueFamilyIndices indices;

				std::uint32_t queueFamilyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);

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

			class PhysicalDevices
			{
			public:
				void init(VDeleter<VkInstance>* instance)
				{
					m_instance = instance;
					findGPUs();
				}

				auto getDevices() const { return m_devices; }
				auto getBestDevice() const { return m_bestDevice; }

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
						if (isDeviceSuitable(dev))
						{
							m_candidateDevices[calculateDeviceScore(dev)] = dev;
						}
					}

					m_bestDevice = m_candidateDevices.begin()->second;

					// TODO: This should be also expected in release mode...
					Expects(m_bestDevice != VK_NULL_HANDLE, "Failed to find a suitable device");
				}

				std::int64_t calculateDeviceScore(VkPhysicalDevice dev)
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

				bool isDeviceSuitable(VkPhysicalDevice dev)
				{
					auto indices = findQueueFamilies(dev);

					return indices.isComplete();
				}

				VkPhysicalDevice m_bestDevice = VK_NULL_HANDLE;
				std::vector<VkPhysicalDevice> m_devices;
				std::map<std::int64_t, VkPhysicalDevice> m_candidateDevices;
				VDeleter<VkInstance>* m_instance;
			};
		}
	}
}

#endif /* TEWI_VULKAN_PHYSICAL_DEVICES_H */
