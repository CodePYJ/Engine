#include "Engine.h"
#include "ExampleLayer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RenderObj.h"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleLayer::ExampleLayer()
	:Layer("Example"),  CameraController(16.0f/ 9.0f)
{
	//obj1 = EE::Renderer2D::CreatObj(vertices2D, "D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/obj.shader");
	//obj2 = EE::Renderer2D::CreatObj(vertices2D, "D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/light.shader");
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
	for (int objID = 0; objID <= EE::Renderer2D::LatestObjID; objID++)
	{
		if (EE::Renderer2D::GetObj(objID)->isLight())
			lightPos = EE::Renderer2D::GetObj(objID)->GetPosition();
		EE::Renderer2D::BeginScene(objID, CameraController.GetCamera());
		EE::Renderer2D::DrawQuad(lightPos);
		EE::Renderer2D::EndScene();
	}
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
	static int item_current_shaderIndex = 0;
	static int item_current_objIndex = 0;
	if (selectedObj && lastID != item_current_objIndex) {
		Reset();
		lastID = item_current_objIndex;
	}
	ImGui::Begin("creatQuad");

	ImGui::SliderFloat3("position", pos, -1.0f, 1.0f);
	ImGui::SliderFloat("rotation", &rotation, 0.0f, 360.0f);
	ImGui::SliderFloat2("size", size, 0.0f, 10.0f);
	ImGui::ColorEdit4("color", color);

	ImGui::BeginListBox("Object Type");
	const char* shader[2] = { "light", "object" };
	for (int i = 0; i < IM_ARRAYSIZE(shader); i++) {
		const bool is_selected = (item_current_shaderIndex == i);
		if (ImGui::Selectable(shader[i], is_selected))
			item_current_shaderIndex = i;
		if (is_selected) {
			ImGui::SetItemDefaultFocus();
		}
	}
	ImGui::EndListBox();

	//EE::Renderer2D::LatestObjID
	for (int i = 0; i <= EE::Renderer2D::LatestObjID; i++) {		//顺序与创建顺序一样，所以i与objID等价
		if (ImGui::Selectable(objNames[i].c_str(), (item_current_objIndex == i))) {
			item_current_objIndex = i;
			selectedObj = EE::Renderer2D::GetObj(i);
		}
	}

	if (ImGui::Button("Create")) {
		item_current_objIndex = EE::Renderer2D::CreatObj(vertices2D, shaderPath[item_current_shaderIndex]);
		selectedObj = EE::Renderer2D::GetObj(item_current_objIndex);
		if (item_current_shaderIndex == 0) {
			EE::Renderer2D::GetObj(item_current_objIndex)->is_light = true;
			objNames.push_back("light");		//每创建一个obj就创建一个objName
		}
		else
			objNames.push_back("object");
	}
	ImGui::End();
	if (selectedObj && lastID == item_current_objIndex) {
		selectedObj->SetPosition({ pos[0], pos[1], pos[2] });
		selectedObj->SetColor({ color[0], color[1], color[2], color[3] });
		selectedObj->SetSize({ size[0], size[1], 1.0f });
		selectedObj->SetRotation(rotation);
	}

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

void ExampleLayer::Reset()
{
	glm::vec3 temPos = selectedObj->GetPosition();
	glm::vec4 temColor = selectedObj->GetColor();
	glm::vec3 temSize = selectedObj->GetSize();
	rotation = selectedObj->GetRotation();
	pos[0] = temPos.x; pos[1] = temPos.y; pos[2] = temPos.z;
	color[0] = temColor.x; color[1] = temColor.y; color[2] = temColor.z; color[3] = temColor.w;
	size[0] = temSize.x; size[1] = temSize.y;
}