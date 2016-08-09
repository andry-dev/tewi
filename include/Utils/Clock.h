#ifndef CLOCK_H
#define CLOCK_H

#include "SDL2/SDL.h"

namespace tewi
{
	namespace Utils
	{
		class Clock
		{
		public:
			Clock();
			~Clock();

			Clock(const Clock& rhs);
			Clock& operator=(const Clock& rhs);

			Clock(Clock&& rhs);
			Clock& operator=(Clock&& rhs);

			double restartTimer();

			inline double getCurrTime() const { return SDL_GetTicks() - m_startTime; }
		private:
			double m_startTime = SDL_GetTicks();
		};
	}
}

#endif /* CLOCK_H */
