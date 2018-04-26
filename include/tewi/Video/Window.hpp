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

#include "asl/string_view"


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

            context.setup();

            windowPtr = glfwCreateWindow(width.value(), height.value(), windowName.data(), nullptr, nullptr);
            TEWI_ENSURES(windowPtr != nullptr, "Window not initialized");

            glfwMakeContextCurrent(windowPtr);

            glfwSetWindowSizeCallback(windowPtr, windowResizeCallback);
            glfwSetErrorCallback(tewi::glfwErrorCallback);

            context.postInit(windowPtr);

            glfwSetWindowUserPointer(windowPtr, usrptr);
        }

        ~Window()
        {
            glfwMakeContextCurrent(0);
            glfwDestroyWindow(windowPtr);
            glfwTerminate();
        }

        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;


        GLFWwindow* windowPtr;
        API::Context<APIType> context;
    };

    template <typename APITag>
    inline bool isWindowClosed(const Window<APITag>& win) noexcept
    {
        return glfwWindowShouldClose(win.windowPtr);
    }

    template <typename APITag>
    inline void forceCloseWindow(Window<APITag>& win) noexcept
    {
        glfwSetWindowShouldClose(win.windowPtr, true);
    }

    template <typename APITag>
    inline void pollWindowEvents(Window<APITag>& win) noexcept
    {
        glfwPollEvents();
    }

    /** Swaps the window buffers
     *
     */
    template <typename APITag>
    inline void swapWindowBuffers(Window<APITag>& win) noexcept
    {
        win.context.swap(win.windowPtr);
    }

    /** Returns the width ofthe window
     *
     */
    template <typename APITag>
    inline tewi::Width getWindowWidth(const Window<APITag>& win) noexcept
    {
        tewi::Width w(0);
        glfwGetWindowSize(win.windowPtr, &w.value(), 0);

        return w;
    }

    /** Returns the height of the window
     *
     */
    template <typename APITag>
    inline tewi::Height getWindowHeight(const Window<APITag>& win) noexcept
    {
        tewi::Height h(0);
        glfwGetWindowSize(win.windowPtr, 0, &h.value());

        return h;
    }

    /** Sets the window keyboard callback
     *
     */
    template <typename APITag>
    inline void setWindowKeyboardCallback(Window<APITag>& win, GLFWkeyfun callback) noexcept
    {
        glfwSetKeyCallback(win.windowPtr, callback);
    }

    /** Sets the window mouse button callback
     *
     */
    template <typename APITag>
    inline void setWindowMouseButtonCallback(Window<APITag>& win, GLFWmousebuttonfun callback) noexcept
    {
        glfwSetMouseButtonCallback(win.windowPtr, callback);
    }

    /** Sets the window mouse cursor callback
     *
     */
    template <typename APITag>
    inline void setWindowMouseCursorPosCallback(Window<APITag>& win, GLFWcursorposfun callback) noexcept
    {
        glfwSetCursorPosCallback(win.windowPtr, callback);
    }


    /** \example window_usage.cpp
     *
     * Shows the usage of the Window class.
     */
}

// well
#include "tewi/Platform/NullRenderer/Window.hpp"
