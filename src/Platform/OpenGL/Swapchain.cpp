#include "tewi/Video/API/Swapchain.hpp"
#include "tewi/Video/API/API.h"

#include "tewi/Video/Window.hpp"
#include "tewi/Video/API/Instance.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Swapchain<API::OpenGLTag>
        {
        public:
            Swapchain(Instance<API::OpenGLTag>&, Window<API::OpenGLTag>&) {  }
        };
    } // namespace API
} // namespace tewi
