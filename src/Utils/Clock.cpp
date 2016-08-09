#include "Utils/Clock.h"

#include <algorithm>

namespace tewi
{
	namespace Utils
	{
		Clock::Clock()
		{
			
		}

		Clock::~Clock()
		{

		}

		Clock::Clock(const Clock& rhs)
			: m_startTime(rhs.m_startTime)
		{
		}

		Clock& Clock::operator=(const Clock& rhs)
		{
			m_startTime = rhs.m_startTime;
			return *this;
		}

		Clock::Clock(Clock&& rhs)
			: m_startTime(std::move(rhs.m_startTime))
		{

		}

		Clock& Clock::operator=(Clock&& rhs)
		{
			m_startTime = std::move(rhs.m_startTime);
			return *this;
		}

		double Clock::restartTimer()
		{
			double currTime = SDL_GetTicks();
			auto elapsed = currTime - m_startTime;
			m_startTime = currTime;

			return elapsed;
		}
	}
}
