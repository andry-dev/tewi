#pragma once

#include <GL/glew.h>

#include "tewi/Video/API/API.h"
#include "tewi/Common.h"
#include "GLFW/glfw3.h"

namespace tewi
{
    /** Common namespace for Graphic API related stuff like context, renderers, etc...
     *
     *
     */
    namespace API
    {
        /** \brief Context initialization; initializes a graphic API for the window.
         *
         * You should *not* instantiate this class without a valid API, only the Window uses this.
         *
         * \tparam APIType The type of the API you want to use. Use one of the
         * structs in API.h or create your own.
         *
         i* \sa Window
         */
        template <typename APIType>
        class TEWI_EXPORT Context final
        {
        public:
            using interface_only = void;

            Context();

            /** Steps before the window is initialized
             *
             */
            void setup();

            /** Steps after the window is initialized
             *
             */
            void postInit(GLFWwindow*);

            /** Steps before drawing
             *
             */
            void preDraw();
            
            /** Steps after drawing
             *
             */
            void postDraw();

            /** Buffer Swap
             *
             */
            void swap(GLFWwindow*);

            /** Returns API information
             *
             */
            const auto getAPIVersion();
        };

    }
}

#include "tewi/Platform/NullRenderer/Context.hpp"
