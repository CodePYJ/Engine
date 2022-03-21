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
		OrthographicCamera GetCamera() { return orthCamera; }
	private:
		void OnMouseScrolled(MouseScrollEvent& e);
		void OnWindowResized(WindowResizeEvent& e);
		
	private:
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		float rotation = 0.0f;
		float translationSpeed = 2.0f, rotationSpeed = 2.0f, zoomLevel = 1.0f;
		float m_aspectRatio;
		OrthographicCamera orthCamera;
	};
}