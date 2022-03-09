#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#define IMGUI_IMPL_OPENGL_LOADER_GLAD
//#include <imgui.h>
//#include <backends/imgui_impl_glfw.h>
//#include <backends/imgui_impl_opengl3.h>

namespace EE {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(1280, 720));
		m_Window->SetEventCallbackFun(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		if (EventType::WindowClose == event.GetEventType())
			OnWindowClose(event);
		EE_TRACE(event.ToString());

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