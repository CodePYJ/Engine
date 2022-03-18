#include "CameraController.h"
#include "Engine/Core/input.h"
#include "Engine/Core/KeyCode.h"

namespace EE {

	OrthCameraController::OrthCameraController(float aspectRatio)
		:m_aspectRatio(aspectRatio), orthCamera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel)
	{

	}

	void OrthCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(GE_KEY_A))
			position.x += translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_D))
			position.x -= translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_W)) {
			zoomLevel -= 0.01;
			zoomLevel = std::max(zoomLevel, 0.09f);
			orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		}
		if (Input::IsKeyPressed(GE_KEY_S)) {
			zoomLevel += 0.01;
			zoomLevel = std::min(zoomLevel, 9.0f);
			orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		}

		orthCamera.SetPosition(position);
	}

	void OrthCameraController::OnEvent()
	{

	}
}