#ifndef TEWI_CLOCK_H
#define TEWI_CLOCK_H

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace tewi
{
	/** \brief Simple timer class.
	 *  
	 * There isn't much to say.
	 *
	 */
	class Clock
	{
	public:
		Clock();
		~Clock();

		Clock(const Clock& rhs);
		Clock& operator=(const Clock& rhs);

		Clock(Clock&& rhs);
		Clock& operator=(Clock&& rhs);

		/** Restarts the timer.
		 *
		 */
		double restartTimer();

		/* Gets the current time.
		 *
		 */
		inline double getCurrTime() const { return glfwGetTime() - m_startTime; }
	private:
		double m_startTime = glfwGetTime();
	};
}

#endif /* TEWI_CLOCK_H */
