#include "tewi/Video/API/Device.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Device<OpenGLTag>
        {
          public:
            Device() {}
        };

    } // namespace API
} // namespace tewi
