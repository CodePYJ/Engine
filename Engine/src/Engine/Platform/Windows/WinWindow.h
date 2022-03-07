#pragma once

#include "Engine/Core/Window.h"
#include <GLFW/glfw3.h>

namespace EE {

	class WinWindow : public Window
	{
	public:
		WinWindow(int width, int height, std::string title = "Engine");
		~WinWindow();

		virtual inline unsigned int GetWidth() override { return m_winData.width; }
		virtual inline unsigned int GetHeight() override { return m_winData.height; }

		virtual void OnUpdate() override;

	private:
		void Init();
		void Shutdown();

	private:
		struct WindowData
		{
			std::string title;
			int width, height;
		};
		WindowData m_winData;

		GLFWwindow* m_Window;
	};

}

