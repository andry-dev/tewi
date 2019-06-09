#pragma once

#include <utility>

#include "tewi/Common.h"

#include <tewi/Utils/Glfw.h>

#include "tewi/Utils/GLFWCallbacks.h"
#include "tewi/Utils/Log.h"
#include "tewi/Utils/Types.h"
#include "tewi/Video/API/Context.hpp"
#include "tewi/Video/WindowEvent.hpp"

#include "asl/ring"
#include "asl/string_view"

namespace tewi
{
    template <typename APIType>
    struct TEWI_EXPORT Window
    {
        Window(asl::string_view windowName, tewi::Width width,
               tewi::Height height);

        ~Window();

        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;

        Window(Window&& rhs)
            : m_windowPtr(std::exchange(rhs.m_windowPtr, nullptr))
        {
        }

        Window& operator=(Window&& rhs) = default;

        GLFWwindow* ptr() noexcept;

        bool isClosed() noexcept;

        void forceClose() noexcept;

        template <typename InputManagerType>
        void pollEvents(InputManagerType& inputManager) noexcept;
        void clear() noexcept;

        void swapBuffers() noexcept;

        tewi::Width getWidth() const noexcept;

        tewi::Height getHeight() const noexcept;

        template <typename InputManagerType>
        void bindTo(InputManagerType& inputManager);

    private:
        GLFWwindow* m_windowPtr;
        tewi::API::Context<APIType> m_context;
    };

    template <typename APIType>
    Window<APIType>::Window(asl::string_view windowName, tewi::Width width,
                            tewi::Height height)
    {
        glfwInit();

        m_context.setup();

        m_windowPtr = glfwCreateWindow(width.value(), height.value(),
                                       windowName.data(), nullptr, nullptr);
        TEWI_ENSURES(m_windowPtr != nullptr, "Window not initialized");
        // glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwMakeContextCurrent(m_windowPtr);

        glfwSetWindowSizeCallback(m_windowPtr, tewi::windowResizeCallback);
        glfwSetErrorCallback(tewi::glfwErrorCallback);

        m_context.postInit(m_windowPtr);
    }

    template <typename APIType>
    Window<APIType>::~Window()
    {
        glfwMakeContextCurrent(nullptr);
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
    template <typename InputManagerType>
    void Window<APIType>::pollEvents(InputManagerType& inputManager) noexcept
    {
        inputManager.preFrame();
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
    tewi::Width Window<APIType>::getWidth() const noexcept
    {
        tewi::Width w(0);
        glfwGetWindowSize(m_windowPtr, &w.value(), 0);

        return w;
    }

    template <typename APIType>
    tewi::Height Window<APIType>::getHeight() const noexcept
    {
        tewi::Height h(0);
        glfwGetWindowSize(m_windowPtr, 0, &h.value());

        return h;
    }

    template <typename APIType>
    GLFWwindow* Window<APIType>::ptr() noexcept
    {
        TEWI_EXPECTS(m_windowPtr, "The internal window pointer is null");
        return m_windowPtr;
    }

    template <typename APIType>
    template <typename InputManagerType>
    void Window<APIType>::bindTo(InputManagerType& inputManager)
    {
        glfwSetWindowUserPointer(m_windowPtr, &inputManager);

        glfwSetKeyCallback(m_windowPtr, &InputManagerType::keyCallback);
    }

} // namespace tewi
