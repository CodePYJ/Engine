#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Renderer/Framebuffer.h"
#include <glm/glm.hpp>
#include "Panels/SceneHierarchyPanel.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Events/KeyEvent.h"


namespace EE {

	class EditorLayer: public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

		void OnKeyPressed(KeyPressedEvent& e);
		void OnMousePressed(MouseButtonPressedEvent& e);
	private:
		EE::Renderer renderer;
		EE::Framebuffer m_Framebuffer;
		SceneHierarchyPanel sceneHierarchyPanel;
		std::shared_ptr<Scene> mScene_ptr;
		glm::vec2 viewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportBounds[2];
		int m_GizmoType = -1;
		Entity selectedEntity= -1;
	};
}