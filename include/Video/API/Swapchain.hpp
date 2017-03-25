#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"
#include "Video/Shader.hpp"
#include "Video/API/Device.hpp"

#include "Video/Window.hpp"

#include "gsl/not_null"

namespace tewi
{
	namespace API
	{
		/** \brief A swapchain.
		 *
		 * \warning API and ABI instable.
		 *
		 */
		template <typename APINum>
		class Swapchain
		{
		public:
			Swapchain(Instance<APINum>&, gsl::not_null<Window<APINum>*>) {  }

			template <typename... Shaders>
			void createPipeline(ShaderPack<Shaders...>& shaders) {  }

			void recreate() {  }

			template <typename... Shaders>
			void replaceShaders(ShaderPack<Shaders...>& shaders) {  }
		};
	}
}
