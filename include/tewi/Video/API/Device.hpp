#pragma once

#include "tewi/Video/API/API.h"
#include "tewi/Video/API/Context.hpp"
#include "tewi/Video/API/Instance.hpp"

#include "tewi/Common.h"

namespace tewi
{
    namespace API
    {
        template <typename APINum>
        class TEWI_EXPORT Device
        {
        public:
            using interface_only = void;

            Device();
        };
    } // namespace API
} // namespace tewi
