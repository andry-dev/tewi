#include "IO/InputManager.h"

namespace tewi
{
    void InputManager::pressKey(asl::u32 keycode)
    {
        m_keymap[keycode] = true;
    }

    void InputManager::releaseKey(asl::u32 keycode)
    {
        m_keymap[keycode] = false;
    }

    bool InputManager::isKeyDown(asl::u32 keycode)
    {
        const auto it = m_keymap.find(keycode);
        if (it != m_keymap.end())
        {
            return it->second;
        }

        return false;
    }

    // TODO(andry): Implement this.
    bool InputManager::isKeyReleased(asl::u32 keycode)
    {
        return false;
    }
} // namespace tewi
