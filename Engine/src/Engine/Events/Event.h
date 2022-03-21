#pragma once

#include "../EEpch.h"
#include "Engine/Core/Core.h"

namespace EE {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory
	{
		None = 0,
		Window, Keyboard, MouseButton
	};

	class EE_API Event {
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() = 0;
		virtual EventCategory GetEventCategory() = 0;
		virtual std::string ToString() { std::string s; return s; };
	};

	class EventDispatcher2
	{
	public:
		using EventCallbackFun = std::function<void(Event&)>;
		//void subscribe(EventCategory eventCategory, EventCallbackFun callbackFun);
		void subscribe(EventType eventType, EventCallbackFun callbackFun);
		void post(Event& event);

	private:
		std::map<EventType, std::vector<EventCallbackFun>> observers;
	};

	class EventDispatcher
	{
	public:
		using EventCallbackFun = std::function<void(Event&)>;

		EventDispatcher(Event& event)
			: m_event(event) { }

		template<typename T, typename F>
		void Dispatch(const F& fun)
		{
			if (m_event.GetEventType() == T::GetStaticType())
				fun(static_cast<T&>(m_event));
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, Event& e)
	{
		return os << e.ToString();
	}
}
