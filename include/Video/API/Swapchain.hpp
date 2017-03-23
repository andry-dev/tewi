#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"
#include "Video/Shader.hpp"
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

			template <typename... Shaders>
			void createPipeline(ShaderPack<Shaders...>& shaders) {  }

			void recreate() {  }

			template <typename... Shaders>
			void replaceShaders(ShaderPack<Shaders...>& shaders) {  }
		};
	}
}
