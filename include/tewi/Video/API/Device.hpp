#pragma once

#include "tewi/Video/API/Context.hpp"
#include "tewi/Video/API/Instance.hpp"
#include "tewi/Video/API/API.h"

#include "tewi/Common.h"

namespace tewi
{
    namespace API
    {
        /** \brief Class that represents a GPU.
         *
         * \warning API and ABI instable.
         *
         */
        template <typename APINum>
        class TEWI_EXPORT Device
        {
        public:
            using interface_only = void;

            Device();
        };
    }
} // namespace API

#include "tewi/Platform/NullRenderer/Device.hpp"
