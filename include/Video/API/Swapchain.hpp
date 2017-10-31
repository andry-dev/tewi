#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"
#include "Video/Shader.hpp"
#include "Video/API/Device.hpp"

#include "Video/Window.hpp"

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

#include "Platform/OpenGL/Swapchain.hpp"
#include "Platform/NullRenderer/Swapchain.hpp"
