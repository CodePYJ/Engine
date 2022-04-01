#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EE {

	void Camera::CalculateViewProjectionMatrix()
	{
		m_view= glm::inverse(glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1))) *
			glm::translate(glm::mat4(1.0f), -1.0f * m_position);
		m_view_projection= m_projection  * m_view;
	}

	void Camera::CalculateProjectionMatrix()
	{
		if (cameraType == ProjectionType::Orthographic) {
			float left = -m_aspectRatio * m_size;
			float right = m_aspectRatio * m_size;
			float top = m_size;
			float bottom = -m_size;

			m_projection= glm::ortho(left, right, bottom, top, o_near, o_far);
		}
		else {
			m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, p_near, p_far);
		}
		CalculateViewProjectionMatrix();
	}

}