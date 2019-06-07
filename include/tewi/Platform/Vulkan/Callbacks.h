#pragma once

#ifdef TEWI_ENABLE_VULKAN

#include "Log.h"
#include "Platform/Vulkan/Common.h"
#include <string>

namespace tewi
{
    namespace Platform
    {
        namespace Vulkan
        {
            inline static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugReportFlagsEXT, VkDebugReportObjectTypeEXT, uint64_t,
                size_t, int32_t, const char*, const char* msg, void* userData)
            {

                std::string strmsg = msg;

                Log::debugInfo("Vulkan validation layer: " + strmsg);

                return VK_FALSE;
            }

            inline VkResult createDebugReportCallbackEXT(
                VkInstance instance,
                const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
                const VkAllocationCallbacks* pAllocator,
                VkDebugReportCallbackEXT* pCallback)
            {
                auto func =
                    (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
                        instance, "vkCreateDebugReportCallbackEXT");
                if (func != nullptr)
                {
                    return func(instance, pCreateInfo, pAllocator, pCallback);
                }
                else
                {
                    return VK_ERROR_EXTENSION_NOT_PRESENT;
                }
            }

            inline void destroyDebugReportCallbackEXT(
                VkInstance instance, VkDebugReportCallbackEXT callback,
                const VkAllocationCallbacks* pAllocator)
            {
                auto func =
                    (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(
                        instance, "vkDestroyDebugReportCallbackEXT");
                if (func != nullptr)
                {
                    func(instance, callback, pAllocator);
                }
            }
        } // namespace Vulkan
    }     // namespace Platform
} // namespace tewi

#endif /* TEWI_ENABLE_VULKAN */
