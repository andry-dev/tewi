#pragma once

#include "tewi/Video/API/API.h"
#include "tewi/Common.h"

#include "tewi/Video/Window.hpp"
#include "tewi/Video/API/Context.hpp"

#include "tewi/Utils/Types.h"


namespace tewi
{
    template <>
    struct TEWI_EXPORT Window<API::NullRendererTag>
    {
    public:
        Window(asl::string_view windowName, Width width, Height height, void* usrptr)
        {
        }

        ~Window() = default;
        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;

        Window(Window&& rhs) = default;
        Window& operator=(Window&& rhs) = default;


        API::Context<API::NullRendererTag> context;
        bool windowClosed = false;
    };

    inline bool isWindowClosed(const Window<API::NullRendererTag>& win) noexcept
    {
        return win.windowClosed;
    }

    inline void forceCloseWindow(Window<API::NullRendererTag>& win) noexcept
    {
        win.windowClosed = true;
    }

    inline void pollWindowEvents(Window<API::NullRendererTag>&) noexcept
    { }

    inline void swapWindowBuffers(Window<API::NullRendererTag>&) noexcept
    { }

    inline tewi::Width getWindowWidth(const Window<API::NullRendererTag>&) noexcept
    {
        return tewi::Width{0};
    }

    inline tewi::Height getWindowHeight(const Window<API::NullRendererTag>&) noexcept
    {
        return tewi::Height{0};
    }

    void setWindowKeyboardCallback(Window<API::NullRendererTag>&, GLFWkeyfun) noexcept
    { }

    void setWindowMouseButtonCallback(Window<API::NullRendererTag>&, GLFWmousebuttonfun) noexcept
    { }

    void setWindowMouseCursorPosCallback(Window<API::NullRendererTag>&, GLFWcursorposfun) noexcept
    { }



} // namespace tewi
