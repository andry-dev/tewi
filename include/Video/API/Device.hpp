#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"
#include "Video/API/API.h"

#include "Common.h"

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

#include "Platform/OpenGL/Device.hpp"
#include "Platform/NullRenderer/Device.hpp"
