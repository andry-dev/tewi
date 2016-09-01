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
	class GameCommon
	{
	public:
		GameCommon(const std::string& windowName, int width, int height)
		{
			m_window = std::make_unique<Video::Window>(windowName, width, height);
			Log::info("CALLED GameCommon::GameCommon");
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
			while (SDL_PollEvent(&m_event))
			{
				switch (m_event.type)
				{
					case SDL_QUIT:
						m_isWindowClosed = true;
						break;

					case SDL_KEYDOWN:
						m_inputManager.pressKey(m_event.key.keysym.sym);
						break;

					case SDL_KEYUP:
						m_inputManager.releaseKey(m_event.key.keysym.sym);
						break;

					case SDL_MOUSEBUTTONDOWN:
						m_inputManager.pressKey(m_event.button.button);
						break;

					case SDL_MOUSEBUTTONUP:
						m_inputManager.releaseKey(m_event.button.button);
						break;

					case SDL_MOUSEMOTION:
						m_inputManager.m_mouseCoords = glm::vec2(m_event.button.x, m_event.button.y);
						break;
				}

				impl().processInputs();
			}
		}

		void update()
		{
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

		SDL_Event m_event;

		IO::InputManager m_inputManager;
	private:
		inline Derived& impl() { return *static_cast<Derived*>(this); }

		void run()
		{
			init();
			while (!m_isWindowClosed)
			{
				m_tickTimer.update();

				processInputs();

				update();

				draw();
			}

		}

	};
}

#endif /* GAME_COMMON_H */
