#include "WinWindow.h"
#include "Engine/Events/WindowEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

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
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EE_ASSERT(status,"Failed to initialize GLAD");
		glfwSetWindowUserPointer(m_Window, &m_winData);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.callbackfun(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.callbackfun(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.callbackfun(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.callbackfun(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.callbackfun(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.callbackfun(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.callbackfun(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event((float)xOffset, (float)yOffset);
				data.callbackfun(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.callbackfun(event);
			});
	}

	void WinWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WinWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
	}
}