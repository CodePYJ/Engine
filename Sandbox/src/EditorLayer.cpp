#include "EditorLayer.h"
#include "Engine/ECS/System/RenderSystem.h"
#include "Engine/ECS/Coordinator.h"
#include <imgui/imgui.h>
#include "Engine/Core/Application.h"


namespace EE {

	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_Framebuffer(1600, 900)
	{
		
	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnAttach()
	{
		mScene_ptr = std::make_shared<Scene>();
		sceneHierarchyPanel.SetActiveScene(mScene_ptr);

	}

	void EditorLayer::OnDetach()
	{

	}
	void EditorLayer::OnUpdate(Timestep timestep)
	{

	}

	void EditorLayer::OnImGuiRender()
	{
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

			sceneHierarchyPanel.OnImGuiRender();

			ImGui::Begin("viewport");
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ViewportHovered = ImGui::IsWindowHovered();
			EE::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

			ImVec2 temViewportSzie = ImGui::GetContentRegionAvail();
			if (viewportSize != *((glm::vec2*)&temViewportSzie)) {
				viewportSize = { temViewportSzie.x, temViewportSzie.y };
				m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
				//CameraController.OnResize(viewportSize.x, viewportSize.y);
			}
			unsigned int tex = m_Framebuffer.GetColorAttachmentID();
			ImGui::Image((void*)tex, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::End();

			ImGui::End();
		}
		else {
			//CreatQuadImGui();
			ImGui::Begin("viewPort");
			unsigned int tex = m_Framebuffer.GetColorAttachmentID();
			ImGui::Image((void*)tex, ImVec2{ 800, 450 });
			ImGui::End();
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{

	}

}