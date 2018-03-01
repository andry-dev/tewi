#pragma once

#include "Video/API/Device.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Device<NullRendererTag>
        {
        public:
        };
    } // namespace API
} // namespace tewi
