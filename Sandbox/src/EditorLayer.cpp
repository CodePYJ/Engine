#include "EditorLayer.h"
#include "Engine/ECS/System/RenderSystem.h"
#include "Engine/ECS/Coordinator.h"
#include <imgui/imgui.h>
#include "Engine/Core/Application.h"
#include "ImGuizmo.h"

#include "Engine/Math/Math.h"
#include "Engine/Core/KeyCode.h"

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
		m_Framebuffer.Bind();
		mScene_ptr->OnUpdate(timestep);
		m_Framebuffer.Unbind();
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
			ImGuiStyle& style = ImGui::GetStyle();
			float minWinSizeX = style.WindowMinSize.x;
			style.WindowMinSize.x = 370;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			style.WindowMinSize.x = minWinSizeX;

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
			mScene_ptr->SetAspectRatio(temViewportSzie.x, temViewportSzie.y);
			if (viewportSize != *((glm::vec2*)&temViewportSzie)) {
				viewportSize = { temViewportSzie.x, temViewportSzie.y };
				m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
				if(mScene_ptr->GetActiveCamera()!=-1 && mScene_ptr->GetCooptr()->HasComponent<CameraComponent>(mScene_ptr->GetActiveCamera()))
					mScene_ptr->GetComponent<CameraComponent>(mScene_ptr->GetActiveCamera()).cameraController->OnResize(viewportSize.x, viewportSize.y);
			}
			unsigned int tex = m_Framebuffer.GetColorAttachmentID();
			ImGui::Image((void*)tex, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			//Gizmos
			Entity selectedEntity = mScene_ptr->GetSelectedEntity();
			Entity activeCamera  = mScene_ptr->GetActiveCamera();
			if (selectedEntity != -1  && activeCamera != -1) {
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();

				float windowWidth = (float)ImGui::GetWindowWidth();
				float windowHeight = (float)ImGui::GetWindowHeight();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
				//Camera
				Entity cam = mScene_ptr->GetActiveCamera();
				auto cameraController = mScene_ptr->GetComponent<CameraComponent>(cam).cameraController;
				auto& cameraTrans = mScene_ptr->GetComponent<TransformComponent>(cam);
				glm::mat4 camProjection = cameraController->GetCamera().GetProjectionMatrix();
				glm::mat4 camView = glm::inverse(cameraTrans.GetTransform());
				//glm::mat4 camView = cameraController->GetCamera().GetViewMatrix();
				//Transform
				auto& transData = mScene_ptr->GetComponent<TransformComponent>(selectedEntity);
				glm::mat4 transform = transData.GetTransform();

				ImGuizmo::Manipulate(glm::value_ptr(camView), glm::value_ptr(camProjection),
					(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));

				if (ImGuizmo::IsUsing()) {
					glm::vec3 translation, rotation, scale;
					Math::DecomposeTransform(transform, translation, rotation, scale);
					transData.position = translation;
					glm::vec3 deltaRotation = rotation - transData.rotation;
					transData.rotation += deltaRotation;
					transData.scale = scale;
				}
			}

			ImGui::End();

			ImGui::End();
		}
		else {
			//CreatQuadImGui();
			ImGui::Begin("viewPort");
			unsigned int tex = m_Framebuffer.GetColorAttachmentID();
			ImGui::Image((void*)tex, ImVec2{ viewportSize.x, viewportSize.y });
			ImGui::End();
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		mScene_ptr->OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&EditorLayer::OnKeyPressed, this, std::placeholders::_1));
	}

	void EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		bool control = Input::IsKeyPressed(GE_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GE_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(GE_KEY_LEFT_SHIFT) || Input::IsKeyPressed(GE_KEY_RIGHT_SHIFT);
		switch (e.GetKeyCode())
		{
		// Gizmos
		case GE_KEY_Q:
			if(control)
				m_GizmoType = -1;
			break;
		case GE_KEY_W:
			if (control)
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case GE_KEY_E:
			if (control)
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		case GE_KEY_R:
			if (control)
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
	}

}