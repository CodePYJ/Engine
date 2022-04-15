#pragma once

//#include "Engine/Events/Event.h"
#include "Camera.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/WindowEvent.h"
#include "Engine/Core/MouseCodes.h"


namespace EE {

	class CameraController
	{
	public:
		CameraController(float aspectRatio);
		void OnUpdate(Timestep ts, bool block);
		void OnEvent(Event& e);
		void OnResize(float w, float h);
		Camera& GetCamera() { return m_camera; }

		float GetOrthoSize() { return zoomLevel; }
		void SetOrthoSize(float size) { zoomLevel = size; m_camera.SetOrthographicSize(zoomLevel); }
		float GetOrthoNear() { return m_camera.GetOrthographicNearClip(); }
		void SetOrthoNear(float n) { m_camera.SetOrthographicNearClip(n); }
		float GetOrthoFar() { return m_camera.GetOrthographicFarClip(); }
		void SetOrthoFar(float f) { m_camera.SetOrthographicFarClip(f); }

		float GetPerspFov() { return m_camera.GetPerspectiveVerticalFOV(); }
		void SetPerspFov(float fov) { m_camera.SetPerspectiveVerticalFOV(fov); }
		float GetPerspNear() { return m_camera.GetPerspectiveNearClip(); }
		void SetPerspNear(float n) { m_camera.SetPerspectiveNearClip(n); }
		float GetPerspFar() { return m_camera.GetPerspectiveFarClip(); }
		void SetPerspFar(float f) { m_camera.SetPerspectiveFarClip(f); }

		glm::vec3 GetPosition() { return m_position; }
		void SetPosition(glm::vec3 position) { m_position = position; }//m_camera.SetPosition(position);
		glm::vec3 GetRotation() { return m_rotation; }
		void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }//m_camera.SetRotation(rotation);
		Camera::ProjectionType GetCameraType() { return m_camera.GetProjectionType(); }
		void SetCameraType(Camera::ProjectionType type) { m_camera.SetProjectionType(type); }

	private:
		void OnMouseScrolled(MouseScrollEvent& e);
		void OnMousePressed(MouseButtonPressedEvent& e);
		void OnMouseReleased(MouseButtonReleasedEvent& e);
		void OnWindowResized(WindowResizeEvent& e);
		void CameraRotate_RBP(glm::vec2 delta);
		void CameraRotate_LBP(glm::vec2 delta);

	private:
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_temp_rotation = { 0.0f, 0.0f, 0.0f };

		float translationSpeed = 2.5f, rotationSpeed = 2.0f, zoomLevel = 1.0f;
		float m_aspectRatio = 0.0f;
		glm::vec2 mouseInitialPos_right = { 0.0f, 0.0f };
		glm::vec2 mouseInitialPos_left = { 0.0f, 0.0f };
		Camera m_camera;
		glm::vec3 m_focal_point = { 0.0, 0.0, 0.0 };
		bool mouse_button_falg_right = true;
		bool mouse_button_falg_left = true;

	};

}