#include "Video/API/Swapchain.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Swapchain<NullRendererTag>
        {
        private:
            using api = NullRendererTag;
        public:
            Swapchain(Instance<NullRendererTag>&, Window<NullRendererTag>&) {}

            void secondPhaseInit(const Device<NullRendererTag>&) {}

            template <typename... Shaders>
            void createPipeline(ShaderPack<Shaders...>& shaders) {}

            void recreate() {}

            template <typename... Shaders>
            void replaceShaders(ShaderPack<Shaders...>& shaders) {}
        };
    } // namespace API
} // namespace tewi
