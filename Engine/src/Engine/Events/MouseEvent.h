#pragma once

#include "Event.h"

namespace EE {

	class EE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_x(x), m_y(y) { }

		inline float GetX() { return m_x; }
		inline float GetY() { return m_y; }

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() { return EventType::MouseMoved; }
		virtual int GetEventCategory() { return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_x << ", " << m_y;
			return ss.str();
		}
	private:
		float m_x, m_y;
	};

	class EE_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(const float x, const float y)
			:offectX(x), offectY(y) { }

		float GetXOffset() const { return offectX; }
		float GetYOffset() const { return offectY; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}


		virtual int GetEventCategory() { return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput; }
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() { return EventType::MouseScrolled; }

	private:
		float offectX, offectY;
	};

	class EE_API MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			:m_button(button) { }

		virtual int GetEventCategory() { return EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput; }

		int GetButton() { return m_button; }

	protected:
		int m_button;
	};

	class EE_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) { }

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
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

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() { return EventType::MouseButtonReleased; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
	};
}
