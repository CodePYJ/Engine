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
			if (Input::IsMouseButtonPressed(Mouse::ButtonRight)) {
				glm::vec2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
				glm::vec2 delta = (mousePos - mouseInitialPos) * 0.006f;
				mouseInitialPos = mousePos;
				float threshold = 0.02f;
				m_position -= m_camera.right_vector * (delta.x > threshold || delta.x < -threshold ? delta.x : 0.0f);
				m_position += m_camera.up_vector * (delta.y > threshold || delta.y < -threshold ? delta.y : 0.0f);
				gaze_point -= m_camera.right_vector * (delta.x > threshold || delta.x < -threshold ? delta.x : 0.0f);
				gaze_point += m_camera.up_vector * (delta.y > threshold || delta.y < -threshold ? delta.y : 0.0f);
			}

			if (button_flag && Input::IsMouseButtonPressed(Mouse::ButtonLeft)) {
				glm::vec2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
				glm::vec2 delta = mousePos - mouseInitialPos;
				mouseInitialPos = mousePos;
				CameraRotate_LBP(delta);
			}
		}

		m_camera.SetPosition(m_position);
		m_camera.SetRotation(m_rotation);
		m_camera.SetGazePoint(gaze_point);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CameraController::OnWindowResized, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&CameraController::OnMousePressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&CameraController::OnMouseReleased, this, std::placeholders::_1));
	}

	void CameraController::OnResize(float w, float h)
	{
		m_aspectRatio = w / h;
		m_camera.SetViewPort(m_aspectRatio);
	}

	void CameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		m_position += e.GetYOffset() * 0.25f * m_camera.lookat;
	}

	void CameraController::OnMousePressed(MouseButtonPressedEvent& e)
	{
		//glfw只会捕获一次按键，持续按下会action会变为repeat
		glm::vec2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
		mouseInitialPos = mousePos;

		if (e.GetButton() == Mouse::ButtonLeft) {
			r_vertical = m_camera.GetR();
			r_horizontal = r_vertical * cos(m_rotation.x);
			button_flag = true;
		}
		if (e.GetButton() == Mouse::ButtonRight) {
		}
	}

	void CameraController::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetButton() == Mouse::ButtonRight) {

		}
		if (e.GetButton() == Mouse::ButtonLeft) {
			button_flag = false;
		}
	}

	void CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
	}

	void CameraController::CameraMove(glm::vec2 delta)
	{

	}

	void CameraController::CameraRotate_LBP(glm::vec2 delta)
	{
		glm::vec3 rotation = glm::degrees(m_rotation);
		rotation.x += delta.y * 0.08f;
		rotation.y += delta.x * 0.08f;
		m_rotation = glm::radians(rotation);
		m_position.x = -r_horizontal * sin(m_rotation.y);
		m_position.z = r_horizontal * cos(m_rotation.y);
		m_position.y = r_vertical * sin(m_rotation.x);
		m_position += m_camera.gaze_point;
	}
}