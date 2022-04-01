#include "CameraController.h"
#include "Engine/Core/input.h"
#include "Engine/Core/KeyCode.h"

namespace EE {

	CameraController::CameraController(float aspectRatio)
	{
		m_camera.SetViewPort(aspectRatio);
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(GE_KEY_A))
			m_position.x -= translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_D))
			m_position.x += translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_W))
			m_position.y += translationSpeed * ts.GetSecond();
		if (Input::IsKeyPressed(GE_KEY_S))
			m_position.y -= translationSpeed * ts.GetSecond();

		//if (Input::IsKeyPressed(GE_KEY_Q))
		//	m_rotation += rotationSpeed * ts.GetSecond();
		//if (Input::IsKeyPressed(GE_KEY_E))
		//	m_rotation -= rotationSpeed * ts.GetSecond();

		if (m_rotation > 180.0f)
			m_rotation -= 360.0f;
		else if (m_rotation <= -180.0f)
			m_rotation += 360.0f;

		m_camera.SetPosition(m_position);
		m_camera.SetRotation(m_rotation);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CameraController::OnWindowResized, this, std::placeholders::_1));
	}

	void CameraController::OnResize(float w, float h)
	{
		m_aspectRatio = w / h;
		m_camera.SetViewPort(m_aspectRatio);
	}

	void CameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		zoomLevel -= e.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		m_camera.SetOrthographicSize(zoomLevel);
	}

	void CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
	}
}