#include "EditorLayer.h"
//#include "Engine/ECS/System/Render2DSystem.h"
#include "Engine/ECS/Coordinator.h"
#include <imgui/imgui.h>
#include "Engine/Core/Application.h"
#include "ImGuizmo.h"

#include "Engine/Math/Math.h"
#include "Engine/Core/KeyCode.h"
#include "Engine/Core/MouseCodes.h"
#include "Engine/Scene/SceneSerializer.h"
#include "Engine/Platform/Windows/FileDialogs.h"


namespace EE {

	extern const std::filesystem::path assetsPath;

	EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{
		
	}

	EditorLayer::~EditorLayer()
	{
		Renderer2D::Shutdown();
	}

	void EditorLayer::OnAttach()
	{
		mScene_ptr = std::make_shared<Scene>();
		sceneHierarchyPanel.SetActiveScene(mScene_ptr);
		Renderer2D::RendererInit();
		FramebufferSpecification fbSpec;
		fbSpec.Attachments = {
			{FramebufferTextureFormat::RGBA8, FramebufferTextureDataFormat::UNSIGNED_BYTE},
			{FramebufferTextureFormat::RED_INTEGER, FramebufferTextureDataFormat::UNSIGNED_BYTE},
			{FramebufferTextureFormat::Depth, FramebufferTextureDataFormat::None}
		};
		fbSpec.Width = 1600;
		fbSpec.Height = 900;
		m_Framebuffer.SetFramebufferSpec(fbSpec);
		m_Framebuffer.Init();
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		m_Framebuffer.Bind();
		renderer.Clear();
		m_Framebuffer.ClearAttachment(1, -1);

		mScene_ptr->OnUpdate(timestep);

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			selectedEntity = m_Framebuffer.ReadPixel(1, mouseX, mouseY);
			//EE_TRACE(selectedEntity);
		}

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
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
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
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);

					if (ImGui::MenuItem("New", "Ctrl+N"))
						NewScene();

					if (ImGui::MenuItem("Open...", "Ctrl+O"))
						OpenScene();

					if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
						SaveSceneAs();

					if (ImGui::MenuItem("Close", NULL, false))
						dockspaceOpen = false;
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			//	Panels
			sceneHierarchyPanel.OnImGuiRender();
			contentBrowserPanel.OnImGuiRenderer();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("viewport");
			auto viewportOffset = ImGui::GetCursorPos(); // Includes tab bar

			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ViewportHovered = ImGui::IsWindowHovered();
			EE::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused);
			mScene_ptr->SetBlock(m_ViewportHovered);//update
			ImVec2 temViewportSzie = ImGui::GetContentRegionAvail();
			mScene_ptr->SetAspectRatio(temViewportSzie.x, temViewportSzie.y);
			if (viewportSize != *((glm::vec2*)&temViewportSzie)) {
				viewportSize = { temViewportSzie.x, temViewportSzie.y };
				m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
				if(mScene_ptr->GetActiveCamera() != -1)
					mScene_ptr->GetComponent<CameraComponent>(mScene_ptr->GetActiveCamera()).cameraController->OnResize(viewportSize.x, viewportSize.y);
			}
			unsigned int tex = m_Framebuffer.GetColorAttachmentID(0);
			ImGui::Image((void*)tex, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			auto windowSize = ImGui::GetWindowSize();
			ImVec2 minBound = ImGui::GetWindowPos();
			minBound.x += viewportOffset.x;
			minBound.y += viewportOffset.y;

			ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
			m_ViewportBounds[0] = { minBound.x, minBound.y };
			m_ViewportBounds[1] = { maxBound.x, maxBound.y };

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					const wchar_t* path = (const wchar_t*)payload->Data;
					OpenScene(std::filesystem::path(assetsPath) / path);
				}
				ImGui::EndDragDropTarget();
			}

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
				//glm::mat4 camView = glm::inverse(cameraTrans.GetTransform());
				glm::mat4 camView = cameraController->GetCamera().GetViewMatrix();
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
			ImGui::PopStyleVar();	//viewport

			ImGui::End();
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		mScene_ptr->OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&EditorLayer::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&EditorLayer::OnMousePressed, this, std::placeholders::_1));
	}

	void EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		bool control = Input::IsKeyPressed(GE_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GE_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(GE_KEY_LEFT_SHIFT) || Input::IsKeyPressed(GE_KEY_RIGHT_SHIFT);
		switch (e.GetKeyCode())
		{
		// Gizmos
		case GE_KEY_Z:
			if(control)
				m_GizmoType = -1;
			break;
		case GE_KEY_X:
			if (control)
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case GE_KEY_C:
			if (control)
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		case GE_KEY_V:
			if (control)
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
	}

	void EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
	{
		if (e.GetButton() == Mouse::ButtonLeft) {
			if(m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(GE_KEY_LEFT_ALT))
				sceneHierarchyPanel.SetSelectedEntity(selectedEntity);
		}
	}

	void EditorLayer::NewScene()
	{
		mScene_ptr = std::make_shared<Scene>();
		sceneHierarchyPanel.SetActiveScene(mScene_ptr);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Engine Scene (*.engine)\0*.engine\0");
		if (!filepath.empty())
		{
			OpenScene(filepath);
		}
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if (path.extension().string() != ".engine")
		{
			EE_WARN("Could not load {0} - not a scene file");
			return;
		}

		mScene_ptr = std::make_shared<Scene>();

		SceneSerializer serializer(mScene_ptr);
		if (serializer.Deserialize(path.string()))
		{
			sceneHierarchyPanel.SetActiveScene(mScene_ptr);
			mScene_ptr->GetComponent<CameraComponent>(mScene_ptr->GetActiveCamera()).cameraController->OnResize(viewportSize.x, viewportSize.y);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Engine Scene (*.engine)\0*.engine\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(mScene_ptr);
			serializer.Serialize(filepath);
		}
	}
}