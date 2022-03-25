#pragma once

#include "Engine/EEpch.h"
#include "Event.h"

namespace EE {

	class EE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) { }

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() { return EventType::WindowResize; }
		virtual int GetEventCategory() { return EventCategory::EventCategoryApplication; }

		unsigned int GetWidth() { return m_width; }
		unsigned int GetHeight() { return m_height; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

	private:
		unsigned int m_width, m_height;
	};

	class EE_API	WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() { return EventType::WindowClose; }
		virtual int GetEventCategory() { return EventCategory::EventCategoryApplication; }

	};
}
