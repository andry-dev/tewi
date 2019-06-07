#include "tewi/Video/API/Swapchain.hpp"
#include "tewi/Video/API/API.h"

#include "tewi/Video/API/Instance.hpp"
#include "tewi/Video/Window.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Swapchain<API::OpenGLTag>
        {
          public:
            Swapchain(Instance<API::OpenGLTag>&, Window<API::OpenGLTag>&) {}
        };
    } // namespace API
} // namespace tewi
