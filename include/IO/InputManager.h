#pragma once

#include <unordered_map>

#include "glm/glm.hpp"

#include "Common.h"

namespace tewi
{
    /** \brief Basic input management class.
     *
     * Right now it supports only a keyboard.
     *
     * **Example:**
     *
     * At the moment it's used in \a GameCommon like this:
     *
     * \code
     *
     * // Under one of the key callbacks for GLFW:
     *
     * if (action == GLFW_PRESS)
     *     gc->m_inputManager.pressKey(button);
     * else if (action == GLFW_RELEASE)
     *     gc->m_inputManager.releaseKey(button);
     *
     * \endcode
     *
     * Meanwhile, in client code, under \a processInputs():
     *
     * \code
     *
     * if (m_inputManager.isKeyDown( key_here ))
     * {
     *     // React to the event
     * }
     *
     * \endcode
     *
     * \todo Fix the mouse.
     * \todo Support for joysticks and controllers.
     *
     */
    class TEWI_EXPORT InputManager
    {
    public:

        /** Registers a key in the keymap
         *
         */
        void pressKey(asl::u32 keycode);

        /** Releases a key in the keymap
         *
         */
        void releaseKey(asl::u32 keycode);
        
        /** Checks if the a key is down or not
         *
         * \return true if the key associated to the keycode is pressed.
         */
        bool isKeyDown(asl::u32 keycode);

        /** Checks if a key is released
         *
         * \return true if the key associated to the keycode is released.
         */
        bool isKeyReleased(asl::u32 keycode);

        void setMouseCoords(const glm::vec2& coords)
        {
            m_mouseCoords = coords;
        }

        auto getMouseCoords() const
        {
            return m_mouseCoords;
        }

    private:

        glm::vec2 m_mouseCoords;
        std::unordered_map<std::uint32_t, bool> m_keymap;
    };
} // namespace tewi
