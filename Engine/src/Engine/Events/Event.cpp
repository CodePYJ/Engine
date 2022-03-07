#include "Event.h"


namespace EE {

	void EventDispatcher::subscribe(EventType eventType, EventCallbackFun callbackFun)
	{
		observers[eventType].push_back(callbackFun);
	}

	void EventDispatcher::post(Event& event)
	{
		EventType type = event.GetEventType();

		if (observers.find(type) == observers.end())
			return;

		std::vector<EventCallbackFun> callbackFuns = observers.at(type);
		for (EventCallbackFun fun : callbackFuns)
			fun(event);
	}

}