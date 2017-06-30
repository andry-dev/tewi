#include "Utils/TickTimer.h"

#include <algorithm>

namespace tewi
{
	bool TickTimer::update(double freq)
	{
		bool reset = false;
		if (m_clock.getCurrTime() >= freq)
		{
			m_tickRate = m_ticks;
			m_ticks = 0;
			reset = true;
			m_clock.restartTimer();
		}
		
		++m_ticks;

		return reset;
	}

	double TickTimer::getDeltaTime(double desiredFramerate)
	{
		return m_deltaClock.restartTimer() / (1.0 / desiredFramerate);
	}
} // namespace tewi
