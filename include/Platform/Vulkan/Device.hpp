#pragma once

#include "Video/API/Device.hpp"
namespace tewi
{
	namespace API
	{
		template <>
		class Device<API_TYPE::VULKAN>
		{
		public:
			void init(Instance<API_TYPE::VULKAN>& instance)
			{
			}

			void cleanup()
			{
			}

		private:
			VkInstance m_instance;
		};
	}
}
