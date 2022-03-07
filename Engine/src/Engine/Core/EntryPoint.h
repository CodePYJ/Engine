#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern EE::Application* EE::CreateApplication();

int main()
{
	EE::Application* app = EE::CreateApplication();
	app->Run();
	delete app;
}

#endif
