#include "Event.h"


namespace EE {

	//void EventDispatcher::subscribe(EventCategory eventCategory, EventCallbackFun callbackFun)
	//{
	//	observers[eventCategory].push_back(callbackFun);
	//}

	void EventDispatcher2::subscribe(EventType eventType, EventCallbackFun callbackFun)
	{
		observers[eventType].push_back(callbackFun);
	}

	void EventDispatcher2::post(Event& event)
	{
		EventType type = event.GetEventType();

		if (observers.find(type) == observers.end())
			return;

		std::vector<EventCallbackFun> funs = observers.at(type);
		for (EventCallbackFun fun : funs) {
			fun(event);
		}
	}

}