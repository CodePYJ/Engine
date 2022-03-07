#pragma once

#include "Event.h"

namespace EE {
	class EE_API AppUpdateEvent : public Event
	{
		AppUpdateEvent() = default;
		virtual EventType GetEventType() override { return EventType::AppUpdate; }
	};
}
