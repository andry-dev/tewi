#pragma once

#include "tewi/Common.h"

namespace tewi
{
    struct NoBase
    {
    };

    namespace API
    {
        struct TEWI_EXPORT OpenGLTag
        {
            using base = NoBase;
        };

        struct TEWI_EXPORT VulkanTag
        {
            using base = NoBase;
        };

        struct TEWI_EXPORT NullRendererTag
        {
            using base = NoBase;
        };
    } // namespace API
} // namespace tewi
