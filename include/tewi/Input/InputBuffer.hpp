#pragma once

#include <asl/ring>
#include <gsl/span>

#include "tewi/Video/WindowEvent.hpp"

namespace tewi
{

    class InputBuffer
    {
    public:

        static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);

        void preFrame();

        gsl::span<tewi::WindowEvent> queryEvents();

    private:

        asl::static_ring<tewi::WindowEvent, 32> m_queue;
    };

}
