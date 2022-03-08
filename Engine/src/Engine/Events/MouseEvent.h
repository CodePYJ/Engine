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
		virtual EventCategory GetEventCategory() { return EventCategory::MouseButton; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_x << ", " << m_y;
			return ss.str();
		}
	private:
		int m_x, m_y;
	};

	class EE_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent() = default;

		virtual EventCategory GetEventCategory() { return EventCategory::MouseButton; }
		virtual EventType GetEventType() { return EventType::MouseScrolled; }
	};

	class EE_API MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			:m_button(button) { }

		virtual EventCategory GetEventCategory() { return EventCategory::MouseButton; }

	protected:
		int m_button;
	};

	class EE_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) { }

		virtual EventType GetEventType() { return EventType::MouseButtonPressed; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
	};

	class EE_API MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) { }

		virtual EventType GetEventType() { return EventType::MouseButtonReleased; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
	};
}
