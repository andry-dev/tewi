#ifndef TICK_TIMER_H
#define TICK_TIMER_H

#include "Utils/Clock.h"

#include <cstdint>
#include <cstddef>

namespace tewi
{
	namespace Utils
	{
		class TickTimer
		{
		public:
			TickTimer();
			~TickTimer();

			TickTimer(const TickTimer& rhs);
			TickTimer& operator=(const TickTimer& rhs);

			TickTimer(TickTimer&& rhs);
			TickTimer& operator=(TickTimer&& rhs);

			bool update(double freq = 1.0);

			double getDeltaTime(double desiredFramerate);

			inline std::size_t getTickRate() const { return m_tickRate; }
		private:
			
			std::size_t m_ticks = 0;
			std::size_t m_tickRate = 0;

			Clock m_clock;
			Clock m_deltaClock;
		};
	}
}


#endif /* TIMER_H */
