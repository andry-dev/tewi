#pragma once

#include <utility>

#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "tewi/Common.h"
#include "tewi/Platform/OpenGL/Context.hpp"
#include "tewi/Platform/Vulkan/Context.hpp"
#include "tewi/Utils/Log.h"
#include "tewi/Utils/GLFWCallbacks.h"
#include "tewi/Utils/Types.h"
#include "tewi/Video/WindowEvent.hpp"


#include "asl/string_view"
#include "asl/ring"



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
    struct TEWI_EXPORT Window
    {
        /**
         *
         * \param windowName The name of the window.
         * \param width The width of the window.
         * \param height The height of the window.
         * \param usrptr GLFW's window pointer. See the example page to understand why you __may__ need this.
         */ 
        Window(asl::string_view windowName, Width width, Height height, void* usrptr = nullptr)
        {
            glfwInit();

            m_context.setup();

            m_windowPtr = glfwCreateWindow(width.value(), height.value(), windowName.data(), nullptr, nullptr);
            TEWI_ENSURES(m_windowPtr != nullptr, "Window not initialized");
            glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwMakeContextCurrent(m_windowPtr);

            glfwSetWindowSizeCallback(m_windowPtr, windowResizeCallback);
            glfwSetErrorCallback(tewi::glfwErrorCallback);

            if (!usrptr)
            {
                glfwSetWindowUserPointer(m_windowPtr, this);
                glfwSetKeyCallback(m_windowPtr,
                    [](GLFWwindow* win, int key, int scancode, int action, int mods)
                {
                    auto ptr = static_cast<tewi::Window<APIType>*>(glfwGetWindowUserPointer(win));

                    WindowEvent event;


                    switch (key)
                    {
                    case GLFW_KEY_UNKNOWN:
                        event.type = WindowEvent::Type::Unknown;
                        break;
                    default:
                        event.type = static_cast<WindowEvent::Type>(key);
                    }

                    switch (action)
                    {
                    case GLFW_PRESS:
                        event.action = WindowEvent::Action::Press;
                        break;

                    case GLFW_RELEASE:
                        event.action = WindowEvent::Action::Release;
                        break;

                    case GLFW_REPEAT:
                        event.action = WindowEvent::Action::Repeat;
                        break;
                    default:
                        event.action = WindowEvent::Action::None;
                    }

                    switch (mods)
                    {
                    case GLFW_MOD_SHIFT:
                        event.mod = WindowEvent::Modifier::Shift;
                        break;
                    case GLFW_MOD_ALT:
                        event.mod = WindowEvent::Modifier::Alt;
                        break;
                    case GLFW_MOD_CONTROL:
                        event.mod = WindowEvent::Modifier::Ctrl;
                        break;
                    case GLFW_MOD_SUPER:
                        event.mod = WindowEvent::Modifier::Super;
                        break;
                    default:
                        event.mod = WindowEvent::Modifier::None;
                    }

                    ptr->m_events.push(event);
                });
            }
            else
            {
                glfwSetWindowUserPointer(m_windowPtr, usrptr);
            }

            m_context.postInit(m_windowPtr);

        }

        ~Window()
        {
            glfwMakeContextCurrent(0);
            glfwDestroyWindow(m_windowPtr);
            glfwTerminate();
        }

        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;

        bool isClosed() noexcept
        {
            return glfwWindowShouldClose(m_windowPtr);
        }

        void forceClose() noexcept
        {
            glfwSetWindowShouldClose(m_windowPtr, true);
        }

        void pollEvents() noexcept
        {
            glfwPollEvents();
        }

        void swapBuffers() noexcept
        {
            m_context.swap(m_windowPtr);
        }

        void clear() noexcept
        {
            m_context.preDraw();
        }

        tewi::Width getWidth() noexcept
        {
            tewi::Width w(0);
            glfwGetWindowSize(m_windowPtr, &w.value(), 0);

            return w;
        }

        tewi::Height getHeight() noexcept
        {
            tewi::Height h(0);
            glfwGetWindowSize(m_windowPtr, 0, &h.value());

            return h;
        }

        GLFWwindow* ptr() noexcept
        {
            return m_windowPtr;
        }

        WindowEvent lastEvent()
        {
            return m_events.front();
        }

        WindowEvent consumeEvent()
        {
            return m_events.read();
        }

    private:
        GLFWwindow* m_windowPtr;
        API::Context<APIType> m_context;
        asl::static_ring<WindowEvent, 32> m_events;
    };
}

// well
#include "tewi/Platform/NullRenderer/Window.hpp"
