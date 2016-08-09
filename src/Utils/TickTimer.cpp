#include "Utils/TickTimer.h"

#include <algorithm>

namespace tewi
{
	namespace Utils
	{
		TickTimer::TickTimer()
		{

		}

		TickTimer::~TickTimer()
		{

		}

		TickTimer::TickTimer(const TickTimer& rhs)
			: m_ticks(rhs.m_ticks), m_tickRate(rhs.m_tickRate)
		{

		}

		TickTimer& TickTimer::operator=(const TickTimer& rhs)
		{
			m_ticks = rhs.m_ticks;
			m_tickRate = rhs.m_tickRate;
			return *this;
		}

		TickTimer::TickTimer(TickTimer&& rhs)
			: m_ticks(std::move(rhs.m_ticks)),
			m_tickRate(std::move(rhs.m_tickRate))
		{
			
		}

		TickTimer& TickTimer::operator=(TickTimer&& rhs)
		{
			m_ticks = std::move(rhs.m_ticks);
			m_tickRate = std::move(rhs.m_tickRate);
			return *this;
		}

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
			
			m_ticks++;

			return reset;
		}
	}
}
