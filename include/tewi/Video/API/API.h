#pragma once

#include "tewi/Common.h"

namespace tewi
{
    /** \brief Tells the library that a specific API has no base API.
     *
     */
    struct NoBase {};

    /**
     * \sa examples/api_intro.cpp
     */ 
    namespace API
    {
        /** \brief OpenGL Tag
         *
         * Struct used for API-dependent code.
         *
         */
        struct TEWI_EXPORT OpenGLTag
        {
            using base = NoBase;
        };

        /** \brief Vulkan Tag
         *
         * Struct used for API-dependent code.
         *
         * The "value" is for future use.
         *
         */
        struct TEWI_EXPORT VulkanTag
        {
            using base = NoBase;
        };

        /** \brief Null Renderer Tag
         *
         * Struct used for API-dependent code.
         *
         * This in particular is used for server stuff where you don't want a
         * window.
         *
         */
        struct TEWI_EXPORT NullRendererTag
        {
            using base = NoBase;
        };
    } // namespace API
} // namespace tewi
