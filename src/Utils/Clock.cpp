#include "Utils/Clock.h"

#include <algorithm>

namespace tewi
{
    double Clock::restartTimer()
    {
        double currTime = glfwGetTime();
        auto elapsed = currTime - m_startTime;
        m_startTime = currTime;

        return elapsed;
    }
} // namespace tewi
