#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"
#include "Video/Shader.hpp"
#include "Video/API/Device.hpp"

#include "Video/Window.hpp"

#include "gsl/not_null"

#include "Common.h"

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
		class TEWI_EXPORT Swapchain
		{
		public:
			Swapchain(Instance<APINum>&, Window<APINum>&) {  }

			template <typename... Shaders>
			void createPipeline(ShaderPack<Shaders...>& shaders) {  }

			void secondPhaseInit(const Device<APINum>&) {  }

			void recreate() {  }

			template <typename... Shaders>
			void replaceShaders(ShaderPack<Shaders...>& shaders) {  }
		};
	}
}
