#include "IO/InputManager.h"

namespace tewi
{
	namespace IO
	{
		InputManager::InputManager()
		{

		}

		void InputManager::pressKey(std::uint32_t keycode)
		{
			m_keymap[keycode] = true;
		}

		void InputManager::relaseKey(std::uint32_t keycode)
		{
			m_keymap[keycode] = false;
		}

		bool InputManager::isKeyPressed(std::uint32_t keycode)
		{

			const auto it = m_keymap.find(keycode);
			if (it != m_keymap.end())
				return it->second;
			else
				return false;

			return false;
		}
	}
}
