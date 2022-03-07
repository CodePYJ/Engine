#pragma once

#include "Event.h"

namespace EE {

	class EE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) { }

		virtual EventType GetEventType() { return EventType::WindowResize; }

	private:
		unsigned int m_width, m_height;
	};

	class EE_API	WindowClossEvent
	{
	public:
		WindowClossEvent() = default;

		virtual EventType GetEventType() { return EventType::WindowClose; }

	};
}
