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

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = 0,
		EventCategoryInput = 1<<1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4
	};

	class EE_API Event {
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() = 0;
		virtual int GetEventCategory() = 0;
		virtual std::string ToString() { std::string s; return s; };

		bool IsInCategory(EventCategory category)
		{
			return GetEventCategory() & category;
		}
		bool Handled = false;
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
