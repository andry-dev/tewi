#ifndef TICK_TIMER_H
#define TICK_TIMER_H

#include "Utils/Clock.h"

#include <cstdint>
#include <cstddef>

namespace tewi
{
	/** \brief A timer that keeps track of the various ticks.
	 *
	 * Its main use is to keep track of delta time and the FPSs at which the game is running.
	 *
	 * I honestly can't think of the client using it.
	 *
	 */
	class TickTimer
	{
	public:
		TickTimer();
		~TickTimer();

		TickTimer(const TickTimer& rhs);
		TickTimer& operator=(const TickTimer& rhs);

		TickTimer(TickTimer&& rhs);
		TickTimer& operator=(TickTimer&& rhs);

		/** Updates the clock every \a freq seconds.
		 *
		 */
		bool update(double freq = 1.0);

		/** Returns the delta time based on a desired framerate.
		 *
		 * Basically, choose a "desired framerate" (ie: At what framerate do you want your game to run on average) and use it as \a desiredFramerate.
		 *
		 * Using the result of this function on your objects will ensure that the games runs at the same speed on every computer.
		 *
		 */
		double getDeltaTime(double desiredFramerate);

		/** Returns the current tickrate.
		 *
		 */
		inline std::size_t getTickRate() const { return m_tickRate; }
	private:
		
		std::size_t m_ticks = 0;
		std::size_t m_tickRate = 0;

		Clock m_clock;
		Clock m_deltaClock;
	};
}


#endif /* TIMER_H */
