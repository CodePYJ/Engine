#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EE {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float m_near, float m_far)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, m_near, m_far)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::inverse(glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1))) *
			glm::translate(glm::mat4(1.0f), -1.0f * m_Position);
		//m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix  * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float m_near, float m_far)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, m_near, m_far);
		CalculateViewMatrix();
	}

}