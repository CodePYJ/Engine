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

	private:
		int m_repeatCount;
	};

	class EE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode) { }

		virtual EventType GetEventType() { return EventType::KeyReleased; }
	};

}
