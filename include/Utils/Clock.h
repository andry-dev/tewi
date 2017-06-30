#pragma once

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Common.h"

namespace tewi
{
	/** \brief Simple timer class.
	 *  
	 * There isn't much to say.
	 *
	 */
	class TEWI_EXPORT Clock
	{
	public:
		Clock() = default;
		~Clock() = default;

		Clock(const Clock& rhs) = default;
		Clock& operator=(const Clock& rhs) = default;

		Clock(Clock&& rhs) = default;
		Clock& operator=(Clock&& rhs) = default;

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
} // namespace tewi
