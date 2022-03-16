#include "Sandbox.h"
#include "ExampleLayer.h"


Sandbox::Sandbox()
{
	PushLayer(new ExampleLayer());
}

Sandbox::~Sandbox()
{

}

EE::Application* EE::CreateApplication()
{
	return new Sandbox();
}


