#pragma once

#include "Engine/EEpch.h"
#include "Core.h"
#include "Engine\Events\Event.h"

namespace EE {

	class EE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
		virtual void SetEventCallbackFun(const EventCallbackFn& callback) = 0;
		static Window* Create(unsigned int width, unsigned int height, std::string title = "Engine");
	};
}

