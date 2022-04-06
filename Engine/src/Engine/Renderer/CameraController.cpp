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
		if (Input::IsKeyPressed(GE_KEY_A)) {
			m_position.x -= translationSpeed * ts.GetSecond() * cos(m_rotation.y) * cos(m_rotation.z);
			m_position.z -= translationSpeed * ts.GetSecond() * sin(m_rotation.y) * cos(m_rotation.z);
			m_position.y += translationSpeed * ts.GetSecond() * sin(m_rotation.z) * cos(m_rotation.y);
		}
		if (Input::IsKeyPressed(GE_KEY_D)) {
			m_position.x += translationSpeed * ts.GetSecond() * cos(m_rotation.y * cos(m_rotation.z));
			m_position.z += translationSpeed * ts.GetSecond() * sin(m_rotation.y * cos(m_rotation.z));
			m_position.y -= translationSpeed * ts.GetSecond() * sin(m_rotation.z * cos(m_rotation.y));
		}
		if (Input::IsKeyPressed(GE_KEY_W)) {
			m_position.x += translationSpeed * ts.GetSecond() * sin(m_rotation.z) * cos(m_rotation.x);
			m_position.y += translationSpeed * ts.GetSecond() * cos(m_rotation.z) * cos(m_rotation.x);
			m_position.z -= translationSpeed * ts.GetSecond() * sin(m_rotation.x) * cos(m_rotation.y);
		}
		if (Input::IsKeyPressed(GE_KEY_S)) {
			m_position.x -= translationSpeed * ts.GetSecond() * sin(m_rotation.z) * cos(m_rotation.x);
			m_position.y -= translationSpeed * ts.GetSecond() * cos(m_rotation.z) * cos(m_rotation.x);
			m_position.z += translationSpeed * ts.GetSecond() * sin(m_rotation.x) * cos(m_rotation.y);
		}

		if (Input::IsKeyPressed(GE_KEY_LEFT_ALT)) {
			glm::vec2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = mousePos - mouseInitialPos;
			mouseInitialPos = mousePos;
			if (Input::IsMouseButtonPressed(0)) {	// left:0 right:1
					MouseRotate(delta);
			}
		}
		

		if (m_rotation.z > 180.0f)
			m_rotation.z -= 360.0f;
		else if (m_rotation.z <= -180.0f)
			m_rotation.z += 360.0f;

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

	void CameraController::MouseRotate(glm::vec2 delta)
	{
		glm::vec3 rotation = { glm::degrees(m_rotation.x), glm::degrees(m_rotation.y), glm::degrees(m_rotation.z) };
		rotation.y += delta.x * 0.05f;
		rotation.x += delta.y * 0.05f;
		m_rotation.x = glm::radians(rotation.x);
		m_rotation.y = glm::radians(rotation.y);
	}
}