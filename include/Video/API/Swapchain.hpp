#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"

#include "Video/Window.hpp"

namespace tewi
{
	namespace API
	{
		template <unsigned int APINum>
		class Swapchain
		{
		public:
			Swapchain()
			{
				static_assert(isAPIValid(APINum), "Invalid API number for the swapchain");
			}

			~Swapchain() { }

			void init(Instance<APINum>& instance, Window<APINum>* window) { }
			void cleanup() {  }

			void recreate() { }

		};
	}
}
