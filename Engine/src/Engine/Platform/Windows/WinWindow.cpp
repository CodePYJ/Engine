#include "WinWindow.h"

namespace EE {

	static bool GLFWInitialized = false;

	Window* Window::Create(unsigned int width, unsigned int height, std::string title)
	{
		return new WinWindow(width, height, title);
	}

	WinWindow::WinWindow(int width, int height, std::string title)
	{
		m_winData.width = width;
		m_winData.height = height;
		m_winData.title = title;
		Init();
	}

	WinWindow::~WinWindow()
	{
		Shutdown();
	}

	void WinWindow::Init()
	{
		if (!GLFWInitialized) {
			int success = glfwInit();
			EE_ASSERT(success, "Could not initialize GLFW!");
			GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_winData.width, m_winData.height, m_winData.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_winData);
	}

	void WinWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}