#include "CameraController.h"
#include "Engine/Core/input.h"
#include "Engine/Core/KeyCode.h"

namespace EE {

	OrthCameraController::OrthCameraController(float aspectRatio)
		:m_aspectRatio(aspectRatio), orthCamera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, m_near, m_far)
	{

	}

	void OrthCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(GE_KEY_A))
			position.x -= translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_D))
			position.x += translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_W))
			position.y += translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_S))
			position.y -= translationSpeed * ts.GetSecond();

		if (Input::IsKeyPressed(GE_KEY_Q))
			rotation += rotationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_E))
			rotation -= rotationSpeed * ts.GetSecond();

		if (rotation > 180.0f)
			rotation -= 360.0f;
		else if (rotation <= -180.0f)
			rotation += 360.0f;

		//orthCamera.SetPosition(position);
		//orthCamera.SetRotation(rotation);
	}

	void OrthCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(std::bind(&OrthCameraController::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OrthCameraController::OnWindowResized, this, std::placeholders::_1));
	}

	void OrthCameraController::OnResize(float w, float h)
	{
		m_aspectRatio = w / h;
		orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel, m_near, m_far);
	}


	void OrthCameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		zoomLevel -= e.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		orthCamera.SetProjectionMatrix(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, -zoomLevel, zoomLevel, m_near, m_far);
	}

	void OrthCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
	}
}