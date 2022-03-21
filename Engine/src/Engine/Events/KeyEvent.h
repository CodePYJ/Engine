#pragma once

#include "Event.h"

namespace EE {

	class EE_API KeyEvent : public Event
	{
	public:
		KeyEvent(int keyCode)
			:m_keyCode(keyCode) { }
		
		int GetKeyCode() { return m_keyCode; }
		
	private:
		int m_keyCode;
	};

	class EE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), m_repeatCount(repeatCount) { }

		virtual EventType GetEventType() { return EventType::KeyPressed; }
		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventCategory GetEventCategory() { return EventCategory::Keyboard; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}
	private:
		int m_repeatCount;
	};

	class EE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode) { }

		virtual EventType GetEventType() { return EventType::KeyReleased; }
		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventCategory GetEventCategory() { return EventCategory::Keyboard; }

		std::string ToString() override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << GetKeyCode();
			return ss.str();
		}
	};

}
