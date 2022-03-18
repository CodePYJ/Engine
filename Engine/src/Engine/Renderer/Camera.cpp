#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EE {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -10.0f, 10.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::inverse(glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1))) *
			glm::translate(glm::mat4(1.0f), m_Position);
		//m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * transform * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -10.0f, 10.0f);
		CalculateViewMatrix();
	}

}