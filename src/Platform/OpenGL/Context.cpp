#include "tewi/Video/API/Context.hpp"

// Should come before GLFW
#include <tewi/Platform/OpenGL/GL.h>

#include "GLFW/glfw3.h"
#include "asl/debug_only"

#include "tewi/Common.h"
#include "tewi/Utils/Log.h"

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
        template <>
        Context<tewi::API::OpenGLTag>::Context()
        {
        }

        template <>
        void Context<tewi::API::OpenGLTag>::setup()
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            glfwSwapInterval(0);
        }

        template <>
        void Context<tewi::API::OpenGLTag>::postInit(GLFWwindow*)
        {
            asl::debug_only<GLenum> error = gladLoadGLLoader(
                reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

            TEWI_ENSURES(error, "Failed GLAD initialization");

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

            glEnable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            // glEnable(GL_CULL_FACE);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        template <>
        void Context<tewi::API::OpenGLTag>::preDraw()
        {
            glClearDepth(1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        template <>
        void Context<tewi::API::OpenGLTag>::postDraw()
        {
        }

        template <>
        void Context<tewi::API::OpenGLTag>::swap(GLFWwindow* m_window)
        {
            glfwSwapBuffers(m_window);
        }

        template <>
        auto Context<tewi::API::OpenGLTag>::getAPIVersion()
        {
            return glGetString(GL_VERSION);
        }

        using GLContext = Context<API::OpenGLTag>;
    } // namespace API
} // namespace tewi
