#pragma once

#include "Video/API/Swapchain.hpp"
#include "Video/API/API.h"

namespace tewi
{
	namespace API
	{
		/*
		template <>
		class Swapchain<API::OpenGLTag>
		{
		public:
			Swapchain(Instance<API::OpenGLTag>&, Window<API::OpenGLTag>*) {  }

			void secondPhaseInit(Device<API::OpenGLTag>&) {  }

			template <typename... Shaders>
			void createPipeline(ShaderPack<Shaders...>& shaders) {  }

			void recreate() {  }

			template <typename... Shaders>
			void replaceShaders(ShaderPack<Shaders...>& shaders) {  }
		private:
		};
		*/
	}
}
