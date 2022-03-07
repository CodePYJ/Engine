#pragma once

#include "Event.h"

namespace EE {

	class EE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int x, int y)
			:m_x(x), m_y(y) { }

		inline int GetX() { return m_x; }
		inline int GetY() { return m_y; }

		virtual EventType GetEventType() { return EventType::MouseMoved; }

	private:
		int m_x, m_y;
	};

	class EE_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent() = default;

		virtual EventType GetEventType() { return EventType::MouseScrolled; }
	};

	class EE_API MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			:m_button(button) { }

	private:
		int m_button;
	};

	class EE_API MouseBuuttonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseBuuttonPressedEvent(int button)
			:MouseButtonEvent(button) { }

		virtual EventType GetEventType() { return EventType::MouseButtonPressed; }
	};

	class EE_API MouseBuuttonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseBuuttonReleasedEvent(int button)
			:MouseButtonEvent(button) { }

		virtual EventType GetEventType() { return EventType::MouseButtonReleased }
	};
}
