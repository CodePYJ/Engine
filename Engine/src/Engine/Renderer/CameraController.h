#pragma once

#include "Camera.h"
#include "Engine/Core/Timestep.h"


namespace EE {

	class OrthCameraController
	{
	public:
		OrthCameraController(float aspectRatio);
		void OnUpdate(Timestep ts);
		void OnEvent();

		OrthographicCamera GetCamera() { return orthCamera; }

	private:
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		float translationSpeed = 3.0f, rotationSpeed = 1.0f, zoomLevel = 1.0f;
		float m_aspectRatio;
		OrthographicCamera orthCamera;
	};
}