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

	class EE_API Event {
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() = 0;

	};

	class EventDispatcher
	{
	public:
		using EventCallbackFun = std::function<void(Event&)>;
		void subscribe(EventType eventType, EventCallbackFun callbackFun);
		void post(Event& event);

	private:
		std::map<EventType, std::vector<EventCallbackFun>> observers;
	};
}
