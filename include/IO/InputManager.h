#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

namespace tewi
{
	namespace IO
	{
		class InputManager
		{
		public:
			InputManager();

			void pressKey(std::uint32_t keycode);
			void relaseKey(std::uint32_t keycode);
			
			bool isKeyPressed(std::uint32_t keycode);
		private:
			
			std::unordered_map<std::uint32_t, bool> m_keymap;
		};
	}
}


#endif /* INPUT_MANAGER_H */
