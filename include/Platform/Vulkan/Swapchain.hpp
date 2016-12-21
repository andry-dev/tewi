#pragma once

#include "Video/API/Swapchain.hpp"
#include "Video/API/Instance.hpp"
#include "Platform/Vulkan/Common.h"
#include "Platform/Vulkan/Instance.hpp"
#include "Platform/Vulkan/QueueFamily.h"

#include "Common.h"
#include "Log.h"

#include <vector>
#include <set>

namespace tewi
{
	namespace API
	{
		template<>
		class Swapchain<API_TYPE::VULKAN>
		{
		public:
			Swapchain()
			{
			}

			void init(Instance<API_TYPE::VULKAN>& instance, Window<API_TYPE::VULKAN>* window)
			{
				m_instance = instance.getInstance();
				m_window = window->getWindow();

				DebugOnly<VkResult> res = glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface);
				Ensures(res == VK_SUCCESS, "Can't create Vulkan surface");

				pickPhysicalDevice();
				createLogicalDevice();
				createSwapChain();
			}

			void cleanup()
			{
				vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
				vkDestroyDevice(m_device, nullptr);
				vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
			}

		private:
			void pickPhysicalDevice()
			{
				std::uint32_t deviceCount = 0;
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
				using namespace Platform::Vulkan;
				QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice, m_surface);

				std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
				std::set<int> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};

				float queuePriority = 1.0f;

				for (auto& queueFamily : uniqueQueueFamilies)
				{
					VkDeviceQueueCreateInfo queueCreateInfo = {};
					queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					queueCreateInfo.queueFamilyIndex = queueFamily;
					queueCreateInfo.queueCount = 1;
					queueCreateInfo.pQueuePriorities = &queuePriority;

					queueCreateInfos.push_back(queueCreateInfo);
				}

				VkPhysicalDeviceFeatures deviceFeatures = {};
				VkDeviceCreateInfo createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				createInfo.pQueueCreateInfos = queueCreateInfos.data();
				createInfo.queueCreateInfoCount = queueCreateInfos.size();
				createInfo.pEnabledFeatures = &deviceFeatures;
				createInfo.enabledExtensionCount = g_requiredDeviceExtensions.size();
				createInfo.ppEnabledExtensionNames = g_requiredDeviceExtensions.data();
				
				if (g_validationLayersEnabled)
				{
					createInfo.enabledLayerCount = g_validationLayerList.size();
					createInfo.ppEnabledLayerNames = g_validationLayerList.data();
				}
				else
				{
					createInfo.enabledLayerCount = 0;
				}

				DebugOnly<VkResult> res = vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device);
				Ensures(res == VK_SUCCESS, "Failed to create logical device");

				vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_queue);
				vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_presentQueue);
			}


			bool isDeviceSuitable(VkPhysicalDevice device)
			{
				using namespace Platform::Vulkan;
				QueueFamilyIndices indices = findQueueFamilies(device, m_surface);

				bool extensionsSupported = checkDeviceExtensionSupport(device);

				bool swapChainAdequate = false;
				if (extensionsSupported)
				{
					auto swapChainSupport = querySwapChainSupport(device, m_surface);
					swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentMode.empty();
				}

				return indices.isComplete() && extensionsSupported && swapChainAdequate;
			}

			bool checkDeviceExtensionSupport(VkPhysicalDevice dev)
			{
				std::uint32_t extensionCount;
				vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, nullptr);

				std::vector<VkExtensionProperties> availableExtentensions(extensionCount);
				vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, availableExtentensions.data());

				std::set<std::string> requiredExtensions(g_requiredDeviceExtensions.begin(), g_requiredDeviceExtensions.end());

				for (const auto& ext : availableExtentensions) {
					requiredExtensions.erase(ext.extensionName);
				}

				return requiredExtensions.empty();
			}


			void createSwapChain()
			{
				using namespace Platform::Vulkan;
				auto swapChainSupport = querySwapChainSupport(m_physicalDevice, m_surface);

				auto surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
				auto presentMode = chooseSwapPresentMode(swapChainSupport.presentMode);
				auto extent = chooseSwapExtent(swapChainSupport.capabilities);

				uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
				if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
				{
					imageCount = swapChainSupport.capabilities.maxImageCount;
				}

				VkSwapchainCreateInfoKHR createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				createInfo.surface = m_surface;createInfo.minImageCount = imageCount;
				createInfo.imageFormat = surfaceFormat.format;
				createInfo.imageColorSpace = surfaceFormat.colorSpace;
				createInfo.imageExtent = extent;
				createInfo.imageArrayLayers = 1;
				createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

				auto indices = findQueueFamilies(m_physicalDevice, m_surface);
				uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily, (uint32_t) indices.presentFamily};

				if (indices.graphicsFamily != indices.presentFamily)
				{
					createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
					createInfo.queueFamilyIndexCount = 2;
					createInfo.pQueueFamilyIndices = queueFamilyIndices;
				}
				else
				{
					createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
					createInfo.queueFamilyIndexCount = 0; // Optional
					createInfo.pQueueFamilyIndices = nullptr; // Optional
				}

				createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
				createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				createInfo.presentMode = presentMode;
				createInfo.clipped = VK_TRUE;
				createInfo.oldSwapchain = VK_NULL_HANDLE;

				DebugOnly<VkResult> scresult = vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain);
				Expects(scresult == VK_SUCCESS, "Can't create swapchain");

				vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
				m_swapchainImages.resize(imageCount);
				vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, m_swapchainImages.data());

				m_swapchainImageFormat = surfaceFormat.format;
				m_swapchainExtent = extent;
			}

			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
			{
				if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
				{
					return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
				}

				for (const auto& format : availableFormats)
				{
					if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
					{
						return format;
					}
				}

				return availableFormats[0];
			}

			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
			{
				for (const auto& presentMode : availablePresentModes)
				{
					if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
					{
						return VK_PRESENT_MODE_IMMEDIATE_KHR;
					}
				}

				return VK_PRESENT_MODE_FIFO_KHR;
			}

			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
			{
				if (capabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max())
				{
					return capabilities.currentExtent;
				}
				else
				{
					int width;
					int height;

					glfwGetWindowSize(m_window, &width, &height);

					VkExtent2D actualExtent = {width, height};

					actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
					actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
					
					return actualExtent;
				}
			}

			VkInstance m_instance;
			GLFWwindow* m_window;
			VkDevice m_device;
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

			VkSurfaceKHR m_surface;

			VkSwapchainKHR m_swapchain;
			VkQueue m_queue;
			VkQueue m_presentQueue;
			std::vector<VkImage> m_swapchainImages;
			VkFormat m_swapchainImageFormat;
			VkExtent2D m_swapchainExtent;
		};
	}
}
