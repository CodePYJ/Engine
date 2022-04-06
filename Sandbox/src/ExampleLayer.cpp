#include "Engine.h"
#include "ExampleLayer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RenderObj.h"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static int item_current_shaderIndex = 0;
static int item_current_objIndex = 0;

ExampleLayer::ExampleLayer()
	:Layer("Example"),  CameraController(16.0f/9.0f)//, m_Framebuffer(1600, 900)
{
	
}

ExampleLayer::~ExampleLayer()
{
	EE::Renderer2D::Shutdown();
}

void ExampleLayer::OnUpdate(EE::Timestep timestep)
	{
	/*
	//EE_TRACE(timestep.GetSecond());
	if (m_ViewportFocused)
		CameraController.OnUpdate(timestep);
	m_Framebuffer.Bind();
	renderer.Clear();
	for (int objID = 0; objID <= EE::Renderer2D::LatestObjID; objID++)
	{
		if (EE::Renderer2D::GetObj(objID)->isLight())
			lightPos = EE::Renderer2D::GetObj(objID)->GetPosition();
		EE::Renderer2D::BeginScene(objID, CameraController.GetCamera());
		EE::Renderer2D::DrawQuad(lightPos);
		EE::Renderer2D::EndScene();
	}
	m_Framebuffer.Unbind();
	*/
}

void ExampleLayer::OnEvent(EE::Event& event)
{
	CameraController.OnEvent(event);
}

void ExampleLayer::OnImGuiRender()
{
	/*
	if (selectedObj && lastID != item_current_objIndex) {
		Reset();
		lastID = item_current_objIndex;
	}

	static bool dockspaceEnable = true;
	if (dockspaceEnable) {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::Separator();
				if (ImGui::MenuItem("Close", NULL, false))
					dockspaceOpen = false;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		CreatQuadImGui();

		ImGui::Begin("viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		EE::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 temViewportSzie = ImGui::GetContentRegionAvail();
		if (viewportSize != *((glm::vec2*)&temViewportSzie)) {
			viewportSize = { temViewportSzie.x, temViewportSzie.y };
			m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
			CameraController.OnResize(viewportSize.x, viewportSize.y);
		}
		unsigned int tex = m_Framebuffer.GetColorAttachmentID();
		ImGui::Image((void*)tex, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		ImGui::End();
	}
	else {
		CreatQuadImGui();
		ImGui::Begin("viewPort");
		unsigned int tex = m_Framebuffer.GetColorAttachmentID();
		ImGui::Image((void*)tex, ImVec2{ 800, 450 });
		ImGui::End();
	}

	if (selectedObj && lastID == item_current_objIndex) {
		selectedObj->SetPosition({ pos[0], pos[1], pos[2] });
		selectedObj->SetColor({ color[0], color[1], color[2], color[3] });
		selectedObj->SetSize({ size[0], size[1], 1.0f });
		selectedObj->SetRotation(rotation);
	}
	*/
}

void ExampleLayer::OnKeyPressedEvent(EE::KeyPressedEvent event)
{

}

void ExampleLayer::OnMouseMovedEvent(EE::Event& event)
{

}

void ExampleLayer::Reset()
{
	/*glm::vec3 temPos = selectedObj->GetPosition();
	glm::vec4 temColor = selectedObj->GetColor();
	glm::vec3 temSize = selectedObj->GetSize();
	rotation = selectedObj->GetRotation();
	pos[0] = temPos.x; pos[1] = temPos.y; pos[2] = temPos.z;
	color[0] = temColor.x; color[1] = temColor.y; color[2] = temColor.z; color[3] = temColor.w;
	size[0] = temSize.x; size[1] = temSize.y;*/
}

void ExampleLayer::CreatQuadImGui()
{
	/*
	ImGui::Begin("creatQuad");
	ImGui::SliderFloat3("position", pos, -3.0f, 3.0f);
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
	ImGui::End();//creatQuad
	*/
}