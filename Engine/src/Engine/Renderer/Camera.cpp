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

		float cos_yaw = cos(yaw);
		float cos_roll = cos(roll);
		float cos_pitch = cos(pitch);
		float sin_yaw = sin(yaw);
		float sin_roll = sin(roll);
		float sin_pitch = sin(pitch);

		glm::mat4 T_view = {
			1.0f, 0.0f, 0.0f, -x,
			0.0f, 1.0f, 0.0f, -y,
			0.0f, 0.0f, 1.0f, -z,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		m_rotate_matrix = {
			//gxt						t								g
			cos_yaw * cos_roll, sin_roll * cos_pitch, -sin_yaw * cos_pitch,  0,
			-sin_roll * cos_yaw, cos_roll * cos_pitch, sin_pitch * cos_yaw,  0,
			sin_yaw * cos_roll,  -sin_pitch * cos_roll, cos_yaw * cos_pitch, 0,
						0,									0,								0,				1
		};
		glm::mat4 R_view = glm::inverse(m_rotate_matrix);
		m_view = glm::transpose(R_view) * glm::transpose(T_view);//glsl是列为主
		m_view_projection= m_projection  * m_view;

		r = std::sqrt(x * x + z * z + y * y);

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

	glm::vec3 Camera::GetFrontDirection()
	{
		return glm::vec3(-1.0f*m_rotate_matrix[0][2], -1.0f*m_rotate_matrix[1][2], -1.0f*m_rotate_matrix[2][2]);
	}

}