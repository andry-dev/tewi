#ifndef GAME_COMMON_H
#define GAME_COMMON_H

#include "IO/InputManager.h"
#include "Utils/TickTimer.h"
#include "Video/Window.h"

#include "Log.h"

#include <memory>

namespace tewi
{
	
	template <class Derived>
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	template <class Derived>
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	template <class Derived>
	class GameCommon
	{
	public:
		GameCommon(const std::string& windowName, int width, int height)
		{
			m_window = std::make_unique<Video::Window>(windowName, width, height);
			Log::info("CALLED GameCommon::GameCommon");

			glfwSetWindowUserPointer(m_window->getWindow(), this);

			glfwSetKeyCallback(m_window->getWindow(), keyCallback<Derived>);
			glfwSetMouseButtonCallback(m_window->getWindow(), mouseButtonCallback<Derived>);
		}

		~GameCommon()
		{
			Log::info("CALLED GameCommon::~GameCommon");
		}

	void start()
	{
		run();
	}

	protected:
		void init()
		{
			impl().init();
		}

		void processInputs()
		{
			impl().processInputs();
		}

		void update()
		{
			glfwPollEvents();
			impl().update();
		}

		void draw()
		{
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			impl().draw();
			m_window->swap();
		}
		
		Utils::TickTimer m_tickTimer;

		std::unique_ptr<Video::Window> m_window;

		bool m_isWindowClosed = false;

		IO::InputManager m_inputManager;
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

		friend void keyCallback<Derived>(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouseButtonCallback<Derived>(GLFWwindow* window, int button, int action, int mods);
	};

	// Thanks GLFW
	template <class Derived>
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GameCommon<Derived>* gc = static_cast<GameCommon<Derived>*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS)
			gc->m_inputManager.pressKey(key);
		else if (action == GLFW_RELEASE)
			gc->m_inputManager.releaseKey(key);
	}

	template <class Derived>
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		GameCommon<Derived>* gc = static_cast<GameCommon<Derived>*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS)
			gc->m_inputManager.pressKey(button);
		else if (action == GLFW_RELEASE)
			gc->m_inputManager.releaseKey(button);
	}

}

#endif /* GAME_COMMON_H */
