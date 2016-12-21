#pragma once

#include "Video/API/Instance.hpp"

#include "Platform/Vulkan/Common.h"

#include "Platform/Vulkan/ValidationLayers.h"
#include "Platform/Vulkan/Callbacks.h"
#include "Platform/Vulkan/QueueFamily.h"
#include "Platform/Vulkan/SwapChainDetails.h"
#include "Log.h"
#include "Utils/DebugOnly.h"

#include <array>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

namespace tewi
{
	namespace API
	{
		constexpr std::array<const char*, 1> g_requiredDeviceExtensions =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		namespace
		{
			void destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
				auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
				if (func != nullptr) {
					func(instance, callback, pAllocator);
				}
			}
		}

		template <>
		class Instance<API_TYPE::VULKAN>
		{
		public:
			void init()
			{
				using namespace Platform::Vulkan;

				Expects(g_validationLayersEnabled && Platform::Vulkan::checkValidationLayersAvaibility(), "Validation Layers are not supported");

				// Boilerplate code
				VkApplicationInfo app = {};
				app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				app.pApplicationName = "tewi Vulkan Loader";
				app.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
				app.pEngineName = "tewi";
				app.engineVersion = VK_MAKE_VERSION(0, 0, 1);
				app.apiVersion = VK_API_VERSION_1_0;

				VkInstanceCreateInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				info.pApplicationInfo = &app;

				if (g_validationLayersEnabled)
				{
					info.enabledLayerCount = g_validationLayerList.size();
					info.ppEnabledLayerNames = g_validationLayerList.data();
				}
				else
				{
					info.enabledLayerCount = 0;
				}

				auto exts = getExtensions();

				info.enabledExtensionCount = exts.size();
				info.ppEnabledExtensionNames = exts.data();

				DebugOnly<VkResult> instanceErrorCode = vkCreateInstance(&info, nullptr, &m_instance);
				Ensures(instanceErrorCode == VK_SUCCESS, "Failed to create a Vulkan instance");

				std::uint32_t extCount = 0;
				vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
				std::vector<VkExtensionProperties> extensions(extCount);
				vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensions.data());

				setupDebugCallback();

			}

			void cleanup()
			{
				destroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
				vkDestroyInstance(m_instance, nullptr);
			}

			auto getInstance() { return m_instance; }

		private:

			std::vector<const char*> getExtensions()
			{
				using namespace Platform::Vulkan;
				std::vector<const char*> ext;

				std::uint32_t glfwExtensionCount;
				const char** glfwExtensions  = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

				for (std::size_t i = 0; i < glfwExtensionCount; ++i)
				{
					ext.push_back(glfwExtensions[i]);
				}

				if (g_validationLayersEnabled)
				{
					ext.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
				}

				return ext;
			}

			void setupDebugCallback()
			{
				using namespace Platform::Vulkan;

				if(!g_validationLayersEnabled)
				{
					return;
				}

				VkDebugReportCallbackCreateInfoEXT info = {};
				info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
				info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT
							| VK_DEBUG_REPORT_WARNING_BIT_EXT
							| VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
				info.pfnCallback = debugCallback;

				DebugOnly<VkResult> res = createDebugReportCallbackEXT(m_instance, &info, nullptr, &m_callback);
				Ensures(res == VK_SUCCESS, "Failed to setup debug callback");
			}

			VkInstance m_instance;
			VkDebugReportCallbackEXT m_callback;
		};
	}
}
