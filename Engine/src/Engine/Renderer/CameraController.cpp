#include "CameraController.h"
#include "Engine/Core/input.h"
#include "Engine/Core/KeyCode.h"


namespace EE {

	CameraController::CameraController(float aspectRatio)
	{
		m_camera.SetViewPort(aspectRatio);
	}

	void CameraController::OnUpdate(Timestep ts, bool block)
	{
		if (block) {
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

			if (Input::IsMouseButtonPressed(Mouse::ButtonRight)) {
				glm::vec2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
				if (mouse_button_falg_right) {
					mouseInitialPos_right = mousePos;
					mouse_button_falg_right = false;
				}
				glm::vec2 delta = mousePos - mouseInitialPos_right;
				mouseInitialPos_right = mousePos;
				CameraRotate_RBP(delta);

				if (m_rotation.z > 180.0f)
					m_rotation.z -= 360.0f;
				else if (m_rotation.z <= -180.0f)
					m_rotation.z += 360.0f;
			}

			if (Input::IsKeyPressed(GE_KEY_LEFT_ALT))
				if (Input::IsMouseButtonPressed(Mouse::ButtonLeft)) {
					glm::vec2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
					if (mouse_button_falg_left) {
						mouseInitialPos_left = mousePos;
						mouse_button_falg_left = false;
					}
					glm::vec2 delta = mousePos - mouseInitialPos_left;
					mouseInitialPos_left = mousePos;
					CameraRotate_LBP(delta);
				}
		}

		m_camera.SetPosition(m_position);
		m_camera.SetRotation(m_rotation);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CameraController::OnWindowResized, this, std::placeholders::_1));
		//dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&CameraController::OnMousePressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&CameraController::OnMouseReleased, this, std::placeholders::_1));
	}

	void CameraController::OnResize(float w, float h)
	{
		m_aspectRatio = w / h;
		m_camera.SetViewPort(m_aspectRatio);
	}

	void CameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		if (m_camera.GetProjectionType() == Camera::ProjectionType::Orthographic) {
			zoomLevel -= e.GetYOffset() * 0.25f;
			zoomLevel = std::max(zoomLevel, 0.25f);
			m_camera.SetOrthographicSize(zoomLevel);
		}
		else {
			float fov = m_camera.GetPerspectiveVerticalFOV();
			fov -= e.GetYOffset() * 0.8;
			fov = std::max(fov, 0.0f);
			m_camera.SetPerspectiveVerticalFOV(fov);
		}

	}

	void CameraController::OnMousePressed(MouseButtonPressedEvent& e)
	{
		if (e.GetButton() == Mouse::ButtonLeft) {

		}
		if (e.GetButton() == Mouse::ButtonRight) {
			//glfw只会捕获一次按键，持续按下会action会变为repeat
		}
	}

	void CameraController::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetButton() == Mouse::ButtonRight) {
			mouseInitialPos_right = { 0.0f, 0.0f };
			mouse_button_falg_right = true;
		}
		if (e.GetButton() == Mouse::ButtonLeft) {
			mouseInitialPos_left = { 0.0f, 0.0f };
			mouse_button_falg_left = true;
		}
	}

	void CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
	}

	void CameraController::CameraRotate_RBP(glm::vec2 delta)
	{
		glm::vec3 rotation = { glm::degrees(m_rotation.x), glm::degrees(m_rotation.y), glm::degrees(m_rotation.z) };
		rotation.y += delta.x * 0.08f;
		rotation.x += delta.y * 0.08f;
		m_rotation.x = glm::radians(rotation.x);
		m_rotation.y = glm::radians(rotation.y);
	}

	void CameraController::CameraRotate_LBP(glm::vec2 delta)
	{
		glm::vec3 rotation = { glm::degrees(m_rotation.x), glm::degrees(m_rotation.y), glm::degrees(m_rotation.z) };
		rotation.y += delta.x * 0.08f;
		rotation.x += delta.y * 0.08f;
		m_rotation.x = glm::radians(rotation.x);
		m_rotation.y = glm::radians(rotation.y);
		m_position = m_focal_point - m_camera.GetFrontDirection() * m_camera.GetR();
	}
}