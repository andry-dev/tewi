#ifndef EVENT_SYSTEM_EVENT_H
#define EVENT_SYSTEM_EVENT_H

#include <cstdint>

#include "EventType.h"

namespace tewi
{
    namespace EventSystem
    {
        class Event
        {
        public:
            auto getType()
            {
                return m_eventType;
            }

        protected:
            Event(std::uint32_t eventType)
                : m_eventType(eventType)
            {
            }

        private:
            std::uint32_t m_eventType = EventType::Null_event;
        };
    } // namespace EventSystem
} // namespace tewi

#endif /* EVENT_SYSTEM_EVENT_H */
