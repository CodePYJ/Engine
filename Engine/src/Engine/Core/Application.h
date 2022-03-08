#pragma once

#include "Core.h"
#include "Window.h"

#include <iostream>

namespace EE {

	class EE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
		void OnUpdate();
		void OnWindowClose(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		EventDispatcher dispatcher;
		bool m_Running = true;
	};

	Application* CreateApplication();
}

