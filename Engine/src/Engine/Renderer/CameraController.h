#pragma once

//#include "Engine/Events/Event.h"
#include "Camera.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/WindowEvent.h"


namespace EE {

	class OrthCameraController
	{
	public:
		OrthCameraController(float aspectRatio);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float w, float h);
		OrthographicCamera& GetCamera() { return orthCamera; }

		float GetSize() { return zoomLevel; }
		void SetSize(float size) 
		{ 
			zoomLevel = size; 
			orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel, m_near, m_far);
		}

		float GetNear() { return m_near; }
		float GetFar() { return m_far; }
		void SetNear(float n)
		{
			m_near = n;
			orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel, m_near, m_far);
		}
		void SetFar(float f)
		{
			m_far = f;
			orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel, m_near, m_far);
		}

		glm::vec3 GetPosition() { return position; }
		float GetRotation() { return rotation; }

	private:
		void OnMouseScrolled(MouseScrollEvent& e);
		void OnWindowResized(WindowResizeEvent& e);
		
	private:
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		float rotation = 0.0f;
		float translationSpeed = 2.0f, rotationSpeed = 2.0f, zoomLevel = 1.0f;
		float m_aspectRatio;
		float m_near = -1.0f, m_far = 1.0f;
		OrthographicCamera orthCamera;
	};
}