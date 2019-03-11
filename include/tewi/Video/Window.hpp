#pragma once

#include <utility>

#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "tewi/Common.h"
#include "tewi/Platform/Vulkan/Context.hpp"
#include "tewi/Utils/Log.h"
#include "tewi/Utils/GLFWCallbacks.h"
#include "tewi/Utils/Types.h"
#include "tewi/Video/WindowEvent.hpp"


#include "asl/string_view"
#include "asl/ring"


namespace tewi
{
    namespace details
    {
        template <typename APIType>
        inline static void windowKeyCallback(GLFWwindow* win,
                                             int key,
                                             int scancode,
                                             int action,
                                             int mods);
    }


    template <typename APIType>
    struct TEWI_EXPORT Window
    {
        Window(asl::string_view windowName,
               tewi::Width width,
               tewi::Height height,
               void* usrptr = nullptr);

        ~Window();

        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;

        GLFWwindow* ptr() noexcept;

        bool isClosed() noexcept;
        void forceClose() noexcept;
        void pollEvents() noexcept;
        void swapBuffers() noexcept;
        void clear() noexcept;

        tewi::Width getWidth() noexcept;
        tewi::Height getHeight() noexcept;

        tewi::WindowEvent lastEvent();
        tewi::WindowEvent consumeEvent();

    private:
        GLFWwindow* m_windowPtr;
        tewi::API::Context<APIType> m_context;
        asl::static_ring<WindowEvent, 32> m_events;

        friend
        void tewi::details::windowKeyCallback<APIType>(GLFWwindow* win,
                                                       int key,
                                                       int scancode,
                                                       int action,
                                                       int mods);
    };


    template <typename APIType>
    Window<APIType>::Window(asl::string_view windowName,
                            tewi::Width width,
                            tewi::Height height,
                            void* usrptr)
    {
        glfwInit();

        m_context.setup();

        m_windowPtr = glfwCreateWindow(width.value(),
                                       height.value(),
                                       windowName.data(),
                                       nullptr,
                                       nullptr);
        TEWI_ENSURES(m_windowPtr != nullptr, "Window not initialized");
        glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwMakeContextCurrent(m_windowPtr);

        glfwSetWindowSizeCallback(m_windowPtr, windowResizeCallback);
        glfwSetErrorCallback(tewi::glfwErrorCallback);

        if (!usrptr)
        {
            glfwSetWindowUserPointer(m_windowPtr, this);

            glfwSetKeyCallback(m_windowPtr,
                               tewi::details::windowKeyCallback<APIType>);

                       
        }
        else
        {
            glfwSetWindowUserPointer(m_windowPtr, usrptr);
        }

        m_context.postInit(m_windowPtr);
    }

    template <typename APIType>
    Window<APIType>::~Window()
    {
        glfwMakeContextCurrent(0);
        glfwDestroyWindow(m_windowPtr);
        glfwTerminate();
    }

    template <typename APIType>
    bool Window<APIType>::isClosed() noexcept
    {
        return glfwWindowShouldClose(m_windowPtr);
    }

    template <typename APIType>
    void Window<APIType>::forceClose() noexcept
    {
        glfwSetWindowShouldClose(m_windowPtr, true);
    }

    template <typename APIType>
    void Window<APIType>::pollEvents() noexcept
    {
        glfwPollEvents();
    }

    template <typename APIType>
    void Window<APIType>::swapBuffers() noexcept
    {
        m_context.swap(m_windowPtr);
    }

    template <typename APIType>
    void Window<APIType>::clear() noexcept
    {
        m_context.preDraw();
    }

    template <typename APIType>
    tewi::Width Window<APIType>::getWidth() noexcept
    {
        tewi::Width w(0);
        glfwGetWindowSize(m_windowPtr, &w.value(), 0);

        return w;
    }

    template <typename APIType>
    tewi::Height Window<APIType>::getHeight() noexcept
    {
        tewi::Height h(0);
        glfwGetWindowSize(m_windowPtr, 0, &h.value());

        return h;
    }

    template <typename APIType>
    GLFWwindow* Window<APIType>::ptr() noexcept
    {
        return m_windowPtr;
    }

    template <typename APIType>
    tewi::WindowEvent Window<APIType>::lastEvent()
    {
        return m_events.front();
    }

    template <typename APIType>
    tewi::WindowEvent Window<APIType>::consumeEvent()
    {
        return m_events.read();
    }

    namespace details
    {
        template <typename APIType>
        inline static void windowKeyCallback(GLFWwindow* win,
                                             int key,
                                             int scancode,
                                             int action,
                                             int mods)
        {
            auto ptr = static_cast<tewi::Window<APIType>*>(glfwGetWindowUserPointer(win));

            tewi::WindowEvent event;

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
        }
    }

}

// well
#include "tewi/Platform/NullRenderer/Window.hpp"
