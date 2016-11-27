#ifndef TEWI_INPUT_MANAGER_H
#define TEWI_INPUT_MANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

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
	 * if (m_inputManager.isKeyDown()
	 *
	 * \todo Fix the mouse.
	 * \todo Support for joysticks and controllers.
	 *
	 */
	class InputManager
	{
	public:

		/** Registers a key in the keymap
		 *
		 */
		void pressKey(std::uint32_t keycode);

		/** Releases a key in the keymap
		 *
		 */
		void releaseKey(std::uint32_t keycode);
		
		/** Checks if the a key is down or not
		 *
		 * \return true if the key associated to the keycode is pressed.
		 */
		bool isKeyDown(std::uint32_t keycode);
		
		/** Checks if a key is released
		 *
		 * \return true if the key associated to the keycode is released.
		 */
		bool isKeyReleased(std::uint32_t keycode);

		// Getters and setters are useless in this case
		glm::vec2 m_mouseCoords;

	private:
		
		std::unordered_map<std::uint32_t, bool> m_keymap;
	};
}


#endif /* TEWI_INPUT_MANAGER_H */
