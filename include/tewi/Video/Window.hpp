#pragma once

#include <utility>
#include <string>

#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "tewi/Common.h"
#include "tewi/Platform/OpenGL/Context.hpp"
#include "tewi/Platform/Vulkan/Context.hpp"
#include "tewi/Utils/Log.h"
#include "tewi/Utils/GLFWCallbacks.h"


namespace tewi
{

    /** \brief Basic windowing system
     *
     * This class is the main windowing system.
     *
     * Basically manages the creation and instance of a window.
     * It registers GLFW's callbacks, etc...
     *
     * \a APIType is used to initialize the window with the choosen graphic API.
     *
     * \sa API::Context
     *
     */
    template <typename APIType>
    class TEWI_EXPORT Window
    {
    public:
        /**
         *
         * \param windowName The name of the window.
         * \param width The width of the window.
         * \param height The height of the window.
         * \param usrptr GLFW's window pointer. See the example page to understand why you __may__ need this.
         */ 
        Window(std::string windowName, int width, int height, void* usrptr = nullptr)
            : m_width(width), m_height(height), m_windowName(std::move(windowName))
        {
            glfwInit();

            m_context.setup();

            m_window = glfwCreateWindow(m_width, m_height, windowName.c_str(), nullptr, nullptr);
            TEWI_ENSURES(m_window != nullptr, "Window not initialized");

            glfwMakeContextCurrent(m_window);

            glfwSetWindowSizeCallback(m_window, windowResizeCallback);
            glfwSetErrorCallback(glfwErrorCallback);

            m_context.postInit(m_window);
            std::printf("API Version: %s\n", m_context.getAPIVersion());

            glfwSetWindowUserPointer(m_window, usrptr);
        }

        ~Window()
        {
            glfwDestroyWindow(m_window);
        }

        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;

        /** Is the window closed?
         *
         */
        inline bool isWindowClosed()
        {
            return glfwWindowShouldClose(m_window);
        }

        inline void forceClose()
        {
            glfwSetWindowShouldClose(m_window, true);
        }

        inline void pollEvents()
        {
            glfwPollEvents();
        }

        /** Swaps the window buffers
         *
         */
        inline void swap() noexcept { m_context.swap(m_window); }

        /** Returns the width ofthe window
         *
         */
        inline int getWidth() const noexcept { return m_width; }

        /** Returns the height of the window
         *
         */
        inline int getHeight() const noexcept { return m_height; }

        /** Returns a pointer to the current instance of GLFWwindow
         *
         */
        inline GLFWwindow* getWindow() const noexcept { return m_window; }

        /** Returns a pointer to the current context used to initialize the API
         *
         */
        inline auto& getContext() { return m_context; }

        void setKeyboardCallback(GLFWkeyfun callback)
        {
            glfwSetKeyCallback(m_window, callback);
        }

        void setMouseButtonCallback(GLFWmousebuttonfun callback)
        {
            glfwSetMouseButtonCallback(m_window, callback);
        }

        void setMouseCursorPosCallback(GLFWcursorposfun callback)
        {
            glfwSetCursorPosCallback(m_window, callback);
        }

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        std::string m_windowName;
        API::Context<APIType> m_context;
    };

    /** \example window_usage.cpp
     *
     * Shows the usage of the Window class.
     */
}

// well
#include "Platform/NullRenderer/Window.hpp"
