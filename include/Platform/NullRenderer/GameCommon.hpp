#pragma once

#include "Video/API/API.h"
#include "Common.h"

#include "GameCommon.hpp"

namespace tewi
{

	template <class Derived>
	class TEWI_EXPORT GameCommon<Derived, API::NullRendererTag>
	{
	public:
		GameCommon(const std::string& windowName, int width, int height)
		{
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
			impl().update();
		}

		void draw()
		{
			impl().draw();
		}

		TickTimer m_tickTimer;
		InputManager m_inputManager;
		std::unique_ptr<Window<API::NullRendererTag>> m_window;
		bool m_isWindowClosed = false;

	private:
		inline Derived& impl()
		{
			return *static_cast<Derived*>(this);
		}

		void run()
		{
			init();
			while (!m_window->isWindowClosed())
			{
				m_tickTimer.update();

				// processInputs();

				update();

				// draw();
			}
		}
	};

}
