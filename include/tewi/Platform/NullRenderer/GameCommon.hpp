#pragma once

#include "tewi/Common.h"
#include "tewi/Video/API/API.h"

#include "tewi/GameCommon.hpp"

namespace tewi
{
    template <class Derived>
    class TEWI_EXPORT GameCommon<Derived, API::NullRendererTag>
    {
    public:
        GameCommon(const std::string& windowName, int width, int height)
            : m_swapchain(m_instance, *m_window)
            , m_window(std::make_unique<Window<API::NullRendererTag>>(
                  windowName, width, height, this))
        {
        }

        void start()
        {
            run();
        }

    protected:
        void init()
        {
            impl().init();
        }

        void processInputs()
        {
            impl().processInputs();
        }

        void update()
        {
            impl().update();
        }

        void draw()
        {
            impl().draw();
        }

        auto& getTimer()
        {
            return m_tickTimer;
        }
        auto& getWindow()
        {
            return *m_window.get();
        }
        auto& getInputManager()
        {
            return m_inputManager;
        }
        auto& getAPIInstance()
        {
            return m_instance;
        }
        auto& getSwapchain()
        {
            return m_swapchain;
        }
        auto& getDevice()
        {
            return m_device;
        }

    private:
        inline Derived& impl()
        {
            return *static_cast<Derived*>(this);
        }

        void run()
        {
            init();
            while (!m_window->isWindowClosed())
            {
                m_tickTimer.update();

                // processInputs();

                update();

                // draw();
            }
        }

        TickTimer m_tickTimer;
        InputManager m_inputManager;
        API::Instance<API::NullRendererTag> m_instance;
        API::Swapchain<API::NullRendererTag> m_swapchain;
        API::Device<API::NullRendererTag> m_device;
        std::unique_ptr<Window<API::NullRendererTag>> m_window;
        bool m_isWindowClosed = false;
    };

} // namespace tewi
