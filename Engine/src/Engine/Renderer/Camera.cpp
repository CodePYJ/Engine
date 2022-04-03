#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EE {

	void Camera::CalculateViewProjectionMatrix()
	{
		float x = m_position.x;
		float y = m_position.y;
		float z = m_position.z;
		float pitch = m_rotation.x;
		float yaw = m_rotation.y;
		float roll = m_rotation.z;
		glm::mat4 T_view = {
			1.0f, 0.0f, 0.0f, -x,
			0.0f, 1.0f, 0.0f, -y,
			0.0f, 0.0f, 1.0f, -z,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		glm::mat4 R_view_inverse = {
			//gxt						t								g
			cos(yaw) * cos(roll), sin(roll) * cos(pitch), sin(yaw) * cos(pitch),    0,
			-sin(roll) * cos(yaw), cos(roll) * cos(pitch), -sin(pitch) * cos(yaw),  0,
			sin(yaw) * cos(roll),  -sin(pitch) * cos(roll), -cos(yaw) * cos(pitch), 0,
						0,									0,								0,					 1
		};

		glm::mat4 R_view = glm::inverse(R_view_inverse);
		m_view = glm::transpose(R_view) * glm::transpose(T_view);//glsl是列为主
		//m_view= //glm::inverse(glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1))) *
			//glm::translate(glm::mat4(1.0f), -1.0f * m_position);
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