#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace tewi
{
	namespace IO
	{
		class InputManager
		{
		public:
			InputManager();

			void pressKey(std::uint32_t keycode);
			void releaseKey(std::uint32_t keycode);
			
			bool isKeyPressed(std::uint32_t keycode);
			
			// Getters and setters are useless in this case
			glm::vec2 m_mouseCoords;

		private:
			
			std::unordered_map<std::uint32_t, bool> m_keymap;
		};
	}
}


#endif /* INPUT_MANAGER_H */
