#pragma once

#include <asl/ring>
#include <gsl/span>

#include "tewi/Video/WindowEvent.hpp"

namespace tewi
{
    /// An [InputManager](<> "tewi::InputManager") which can hold more than one
    /// event at a time.
    ///
    /// \module Input-Management
    class InputBuffer
    {
      public:
        /// \exclude
        static void keyCallback(GLFWwindow* win, int key, int scancode,
                                int action, int mods);

        /// \exclude
        void preFrame();

        /// Queries the stored events for the current frame.
        ///
        /// \returns A span referencing the events.
        gsl::span<tewi::WindowEvent> queryEvents();

      private:
        asl::static_ring<tewi::WindowEvent, 32> m_queue;
    };

} // namespace tewi
