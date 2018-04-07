#pragma once

#include "tewi/Video/API/Swapchain.hpp"
#include "tewi/Video/API/API.h"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Swapchain<API::OpenGLTag>
        {
        public:
            Swapchain(Instance<API::OpenGLTag>&, Window<API::OpenGLTag>&) {  }

            void secondPhaseInit(Device<API::OpenGLTag>&) {  }

            template <typename... Shaders>
            void createPipeline(ShaderPack<Shaders...>& shaders) {  }

            void recreate() {  }

            template <typename... Shaders>
            void replaceShaders(ShaderPack<Shaders...>& shaders) {  }
        };
    } // namespace API
} // namespace tewi
