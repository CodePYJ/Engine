#include "Application.h"
#include "Engine/Renderer/Renderer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace EE {

	Application* Application::s_app = nullptr;

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(1600, 900));
		m_Window->SetEventCallbackFun(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		s_app = this;

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_layerstack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerstack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		if (EventType::WindowClose == event.GetEventType())
			OnWindowClose(event);
		//EE_TRACE(event.ToString());

		for (auto it = m_layerstack.end(); it != m_layerstack.begin();) {
			//EE_TRACE((*(it-1))->GetName());
			if (event.Handled) {
				//EE_TRACE(event.Handled);
				break;
			}
			(*--it)->OnEvent(event);
		}
	}

	void Application::OnUpdate()
	{
		glfwPollEvents();
		m_Window->OnUpdate();
	}

	void Application::OnWindowClose(Event& e)
	{
			m_Running = false;
	}

	void Application::OnWindowResize(WindowResizeEvent& e)
	{

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
			m_Minimized = true;

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerstack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerstack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerstack.PushOverlay(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_layerstack.PopOverlay(layer);
	}
}