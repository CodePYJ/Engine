#include "Engine.h"
#include "ExampleLayer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RenderObj.h"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int obj1;

ExampleLayer::ExampleLayer()
	:Layer("Example"),  CameraController(16.0f/ 9.0f)
{
	obj1 = EE::Renderer2D::CreatObj("D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/test.shader");
}

ExampleLayer::~ExampleLayer()
{
	EE::Renderer2D::Shutdown();
}

void ExampleLayer::OnUpdate(EE::Timestep timestep)
	{
	//EE_TRACE(timestep.GetSecond());

	CameraController.OnUpdate(timestep);

	renderer.Clear();

	EE::Renderer2D::BeginScene(obj1, CameraController.GetCamera());
	EE::Renderer2D::DrawQuad(glm::vec2(-0.25,-0.25), rotation, glm::vec2(0.25f, 0.25f), glm::vec4(0.25, 0.6, 0.8, 1.0));
	//EE::Renderer2D::DrawQuad(glm::vec2(0.25, 0.25), rotation, glm::vec2(1.0f, 1.0f), glm::vec4(color[0], color[1], color[2], color[3]));
	EE::Renderer2D::EndScene();


}

void ExampleLayer::OnEvent(EE::Event& event)
{
	//switch (event.GetEventType())
	//{
	//	case EE::EventType::KeyPressed: OnKeyPressedEvent(static_cast<EE::KeyPressedEvent&>(event)); break;
	//	case EE::EventType::MouseMoved: OnMouseMovedEvent(event); break;
	//}
		

}

void ExampleLayer::OnImGuiRender()
{
	//ImGui::Begin("test");
	//ImGui::SliderFloat3("position", tran, -1.0f, 1.0f);
	//ImGui::SliderFloat("rotation", &rotation, 0.0f, 360.0f);
	//ImGui::ColorEdit4("color", color);
	//ImGui::End();
}

void ExampleLayer::OnKeyPressedEvent(EE::KeyPressedEvent event)
{
	//switch (event.GetKeyCode())
	//{
	//	case:
	//}
}

void ExampleLayer::OnMouseMovedEvent(EE::Event& event)
{

}