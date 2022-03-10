#pragma once

#include <iostream>

#include "Core.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"

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
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_app; }

	private:
		std::unique_ptr<Window> m_Window;
		//EventDispatcher dispatcher;
		LayerStack m_layerstack;
		bool m_Running = true;

		static Application* s_app;
		ImGuiLayer* m_ImGuiLayer;
	};

	Application* CreateApplication();
}

