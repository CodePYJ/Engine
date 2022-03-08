#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
}