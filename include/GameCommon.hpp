#ifndef GAME_COMMON_H
#define GAME_COMMON_H

#include "Video/Window.h"
#include "Utils/TickTimer.h"
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
			impl().processInputs();
		}

		void draw()
		{
			impl().draw();
			m_window->swap();
		}
		
		Utils::TickTimer m_tickTimer;
		std::unique_ptr<Video::Window> m_window;
	private:
		inline Derived& impl() { return *static_cast<Derived*>(this); }

		void run()
		{
			init();
			while (!m_window->isWindowClosed())
			{
				m_tickTimer.update();

				processInputs();

				draw();
			}

		}

	};
}

#endif /* GAME_COMMON_H */
