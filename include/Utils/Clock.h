#ifndef CLOCK_H
#define CLOCK_H

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace tewi
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

		inline double getCurrTime() const { return glfwGetTime() - m_startTime; }
	private:
		double m_startTime = glfwGetTime();
	};
}

#endif /* CLOCK_H */
