#pragma once

#include "tewi/Video/API/Instance.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Instance<NullRendererTag>
        {
        public:
        };
    } // namespace API
} // namespace tewi
