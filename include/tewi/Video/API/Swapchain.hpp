#pragma once

#include "tewi/Video/API/Context.hpp"
#include "tewi/Video/API/Instance.hpp"
#include "tewi/Video/Shader.hpp"
#include "tewi/Video/API/Device.hpp"

#include "tewi/Video/Window.hpp"

#include "tewi/Common.h"

namespace tewi
{
    namespace API
    {
        /** \brief A swapchain.
         *
         * \warning API and ABI instable.
         *
         */
        template <typename APIType>
        class TEWI_EXPORT Swapchain
        {
        public:
            using interface_only = void;

            Swapchain(Instance<APIType>&, Window<APIType>&);

            void secondPhaseInit(const Device<APIType>&);

            template <typename... Shaders>
            void createPipeline(ShaderPack<Shaders...>& shaders);

            void recreate();

            template <typename... Shaders>
            void replaceShaders(ShaderPack<Shaders...>& shaders);
        };
    }
}

#include "tewi/Platform/OpenGL/Swapchain.hpp"
#include "tewi/Platform/NullRenderer/Swapchain.hpp"
