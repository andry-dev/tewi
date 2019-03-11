#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "asl/debug_only"

#include "tewi/Common.h"
#include "tewi/Utils/Log.h"
#include "tewi/Video/API/Context.hpp"

namespace tewi
{
    namespace API
    {
        /** \brief OpenGL Context.
         *
         *
         * Initializes OpenGL.
         *
         * **Internal use only.**
         */
        template<>
        class TEWI_EXPORT Context<API::OpenGLTag>
        {
        public:
            Context()
            {
            }

            void setup()
            {
                // FUCKING MESA
                // THIS IS UNDER AMDGPU AND MESA-GIT, I DUNNO IF IT WORKS ON INTEL
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                glfwSwapInterval(0);
            }

            void postInit(GLFWwindow*)
            {
                asl::debug_only<GLenum> error = glewInit();
                TEWI_ENSURES(error == GLEW_OK, "Failed GLEW initialization");

                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

                glEnable(GL_BLEND);
                glEnable(GL_DEPTH_TEST);
                //glEnable(GL_CULL_FACE);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            void preDraw()
            {
                glClearDepth(1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }

            void postDraw()
            {

            }

            void swap(GLFWwindow* m_window)
            {
                glfwSwapBuffers(m_window);
            }

            const unsigned char* getAPIVersion()
            {
                return glGetString(GL_VERSION);
            }
        };

        using GLContext = Context<API::OpenGLTag>;
    }
}
