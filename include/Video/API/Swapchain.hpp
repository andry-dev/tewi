#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"
#include "Video/API/Shader.hpp"
#include "Video/API/Device.hpp"

#include "Video/Window.hpp"

namespace tewi
{
	namespace API
	{
		template <typename APINum>
		class Swapchain
		{
		public:
			Swapchain(Instance<APINum>&, Window<APINum>*) {  }

			void secondPhaseInit(Device<APINum>&) {  }

			void createPipeline(ShaderProgram<APINum>& shaders) { }

			void recreate() { }
		};
	}
}
