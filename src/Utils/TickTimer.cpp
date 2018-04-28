#include "tewi/Utils/TickTimer.h"

#include <algorithm>

namespace tewi
{
#ifdef TEWI_OLD_TICK_TIMER_IMPL
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
#else
    float TickTimer::getDeltaTime() noexcept
    {
        float currentFrame = glfwGetTime();
        delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        return delta;
    }

#endif
} // namespace tewi
