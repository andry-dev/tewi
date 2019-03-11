#include "tewi/IO/InputManager.h"

namespace tewi
{
    void InputManager::pressKey(asl::i32 keycode)
    {
        m_keymap[keycode] = true;
    }

    void InputManager::releaseKey(asl::i32 keycode)
    {
        m_keymap[keycode] = false;
    }

    bool InputManager::isKeyDown(asl::i32 keycode)
    {
        const auto it = m_keymap.find(keycode);
        if (it != m_keymap.end())
        {
            return it->second;
        }

        return false;
    }

    // TODO(andry): Implement this.
    bool InputManager::isKeyReleased(asl::i32 keycode)
    {
        return false;
    }
} // namespace tewi
