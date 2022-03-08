#include "Event.h"


namespace EE {

	void EventDispatcher::subscribe(EventCategory eventCategory, EventCallbackFun callbackFun)
	{
		observers[eventCategory].push_back(callbackFun);
	}

	void EventDispatcher::post(Event& event)
	{
		EventCategory cat = event.GetEventCategory();

		if (observers.find(cat) == observers.end())
			return;

		std::vector<EventCallbackFun> callbackFuns = observers.at(cat);
		for (EventCallbackFun fun : callbackFuns)
			fun(event);
	}

}