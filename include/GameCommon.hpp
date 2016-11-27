#ifndef GAME_COMMON_H
#define GAME_COMMON_H

#include "IO/InputManager.h"
#include "Utils/TickTimer.h"
#include "Video/Window.h"

#include "Log.h"

#include <memory>

#include "Video/API/Context.h"
#include "Platform/Vulkan/Common.h"
#include "Platform/OpenGL/GLContext.h"

namespace tewi
{
	/** Callback for keyboard presses.
	 *
	 * **Internal use only.**
	 */
	template <class Derived, unsigned int APINum>
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/** Callback for mouse presses.
	 *
	 * **Internal use only.**
	 *
	 */
	template <class Derived, unsigned int APINum>
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	/** \brief Managed base game class.
	 *
	 * Inherit from this class to get a managed base game class.
	 *
	 * **If this is your first time seeing this engine and you stumbled upon this class then read:**
	 *
	 * **This class uses a template parameter of type int called *APINum*, use this to switch the used graphic API.**
	 *
	 * **Possible values are listed in the enum API::API_TYPE.**
	 *
	 * **This is a common pattern in the engine.**
	 *
	 * It basically sets up everything for you, so you don't need to lose time writing window creation and game loop management.
	 *
	 * This class uses the CRTP idiom to statically dispatch the function calls, so you **need to implement every function or your program will seg fault.**
	 *
	 * Example in your own code:
	 *
	 * \code
	 *
	 * #include "GameCommon.hpp"
	 *
	 * using namespace tewi;
	 *
	 * class MainGame : public GameCommon<MainGame, API::API_TYPE::OPENGL>
	 * {
	 * public:
	 *    void init();
	 *    void processInputs();
	 *    void update();
	 *    void draw();
	 *
	 * // Your functions
	 * // [...]
	 *
	 *
	 * private:
	 *
	 * // Your variables
	 *
	 * };
	 *
	 * \endcode
	 *
	 * Then, your code is exposed to the protected members of this class.
	 *
	 * **Common Questions:**
	 *
	 *
	 * "How do I dynamically dispatch this?"
	 *
	 * "How do I choose in runtime what API to use?"
	 *
	 * There is a solution that it's not really pretty.
	 *
	 * Let's say you create a class named "MainGame" that inherits from this; what you can do is the following:
	 *
	 * Add a template argument to "MainGame" so that it takes an *unsigned int* and in main.cpp just branch:
	 *
	 * \code
	 *
	 * int main()
	 * {
	 *     // Let's say this is the runtime result based on which you switch API
	 *     bool someEval = ...;
	 *
	 *     if (someEval)
	 *     {
	 *         MainGame<tewi::API::API_TYPE::OPENGL> oglGame;
	 *         oglGame.start()l
	 *     }
	 *     else
	 *     {
	 *         MainGame<tewi::API::API_TYPE::VULKAN> vkGame;
	 *         vkGame.start();
	 *     }
	 *
	 *    return 0;
	 * }
	 *
	 * \endcode
	 *
	 *
	 * This works like you'd expect and in fact provides "runtime" dispatch but there are some caveats:
	 * * It bloats the size of the executable.
	 * * It's not pretty.
	 *
	 * The main concern is the first, but that's the price I'm paying for not using virtual calls.
	 *
	 */
	template <class Derived, unsigned int APINum>
	class GameCommon
	{
	public:
		GameCommon(const std::string& windowName, int width, int height)
		{
			m_window = std::make_unique<Window<APINum>>(windowName, width, height);
			Log::info("CALLED GameCommon::GameCommon");

			glfwSetWindowUserPointer(m_window->getWindow(), this);

			glfwSetKeyCallback(m_window->getWindow(), keyCallback<Derived, APINum>);
			glfwSetMouseButtonCallback(m_window->getWindow(), mouseButtonCallback<Derived, APINum>);
		}

		~GameCommon()
		{
			Log::info("CALLED GameCommon::~GameCommon");
		}


		/** Basically arbitrarily starts the game.
		 *
		 * The constructor alone won't do it for you.
		 *
		 */
		void start()
		{
			run();
		}

	protected:
		/** Initializes the game.
		 * 
		 * This function is called only once, use it to initialize basic game objects.
		 *
		 */
		void init()
		{
			impl().init();
		}

		/** Processes inputs through the input manager.
		 *
		 *
		 * It's the first function that is called in a frame.
		 */
		void processInputs()
		{
			impl().processInputs();
		}

		/** All your update logic goes here (like physics, camera, etc...).
		 *
		 * 
		 *
		 * It's the second function that is called in a frame.
		 *
		 */
		void update()
		{
			glfwPollEvents();
			impl().update();
		}

		/** Draws your entities.
		 *
		 * This is the last function that is called in a frame.
		 *
		 */
		void draw()
		{
			m_window->getContext()->preDraw();
			impl().draw();
			m_window->swap();
		}
		
		TickTimer m_tickTimer;

		std::unique_ptr<Window<APINum>> m_window;

		bool m_isWindowClosed = false;

		InputManager m_inputManager;
	private:
		inline Derived& impl() { return *static_cast<Derived*>(this); }

		void run()
		{
			init();
			while (!m_window->isWindowClosed())
			{
				m_tickTimer.update();

				processInputs();

				update();

				draw();
			}

		}

		// yeah. GLFW.
		friend void keyCallback<Derived, APINum>(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouseButtonCallback<Derived, APINum>(GLFWwindow* window, int button, int action, int mods);
	};

	// Thanks GLFW
	template <class Derived, unsigned int APINum>
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GameCommon<Derived, APINum>* gc = static_cast<GameCommon<Derived, APINum>*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS)
			gc->m_inputManager.pressKey(key);
		else if (action == GLFW_RELEASE)
			gc->m_inputManager.releaseKey(key);
	}

	template <class Derived, unsigned int APINum>
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		GameCommon<Derived, APINum>* gc = static_cast<GameCommon<Derived, APINum>*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS)
			gc->m_inputManager.pressKey(button);
		else if (action == GLFW_RELEASE)
			gc->m_inputManager.releaseKey(button);
	}

}

#endif /* GAME_COMMON_H */
