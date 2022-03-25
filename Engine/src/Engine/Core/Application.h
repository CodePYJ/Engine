#pragma once

#include "Engine/EEpch.h"
#include "Engine/ImGui/ImGuiLayer.h"

#include "Core.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Timestep.h"
#include "Engine/Events/WindowEvent.h"

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

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		inline static Application& Get() { return *s_app; }
		inline void Close() { m_Running = false; }
		void OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_layerstack;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime;

		static Application* s_app;
		ImGuiLayer* m_ImGuiLayer;
	};

	Application* CreateApplication();
}

