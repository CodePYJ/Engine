#include "Application.h"
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
		PushLayer(m_ImGuiLayer);
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

			//glDrawArrays(GL_TRIANGLES, 0, 3);

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
		if (EventType::WindowClose == event.GetEventType())
			OnWindowClose(event);
		//EE_TRACE(event.ToString());

		for (auto it = m_layerstack.end(); it != m_layerstack.begin(); ) {
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

	void Application::PushLayer(Layer* layer)
	{
		m_layerstack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerstack.PopLayer(layer);
	}
}