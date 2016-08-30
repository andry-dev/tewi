#ifndef EVENT_SYSTEM_EVENT_TYPE_H
#define EVENT_SYSTEM_EVENT_TYPE_H

namespace tewi
{
	namespace EventSystem
	{
		enum EventType
		{
			Null_event,

			Mouse_moved,
			Mouse_button_pressed,
			Mouse_wheel_moved,
			
			Key_pressed,

			Object_collided,

			Last_event
		};
	}
}

#endif /* EVENT_SYSTEM_EVENT_TYPE_H */
