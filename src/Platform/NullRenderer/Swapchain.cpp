#include "tewi/Video/API/Swapchain.hpp"
#include "tewi/Video/API/API.h"
#include "tewi/Video/API/Instance.hpp"
#include "tewi/Video/Window.hpp"

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
        };
    } // namespace API
} // namespace tewi
