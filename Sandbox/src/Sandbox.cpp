#include "Sandbox.h"
#include "ExampleLayer.h"
#include "EditorLayer.h"

Sandbox::Sandbox()
{
	//PushLayer(new ExampleLayer());
	PushLayer(new EE::EditorLayer());
}

Sandbox::~Sandbox()
{

}

EE::Application* EE::CreateApplication()
{
	return new Sandbox();
}


