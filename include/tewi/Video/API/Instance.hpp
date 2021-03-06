#pragma once

#include "tewi/Video/API/Context.hpp"

#include "tewi/Common.h"

namespace tewi
{
    namespace API
    {
        /** \brief Class that deals with the instance of a graphic API.
         *
         *
         * The difference between this and Context is that this manages the API
         * it-self while Context is responsible for create the environment for
         * the API. This doesn't deal with the Window (well, Vulkan's does).
         *
         * \warning API and ABI instable.
         */
        template <typename APINum>
        class TEWI_EXPORT Instance
        {
        public:
            using interface_only = void;

            Instance();
        };
    } // namespace API
} // namespace tewi

#include "tewi/Platform/NullRenderer/Instance.hpp"
#include "tewi/Platform/Vulkan/Instance.hpp"
