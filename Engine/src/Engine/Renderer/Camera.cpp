#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EE {

	void Camera::CalculateViewMatrix()
	{		
		glm::mat4 T_view(1.0f);
		T_view[0][3] = -m_position.x;
		T_view[1][3] = -m_position.y;
		T_view[2][3] = -m_position.z;

		lookat = normalize(gaze_point - m_position);
		right_vector = normalize(cross(lookat, glm::vec3(0.0f, 1.0f, 0.0f)));
		up_vector = normalize(cross(right_vector, lookat));

		m_rotate_matrix = {
			right_vector.x, up_vector.x, -lookat.x, 0,
			right_vector.y, up_vector.y, -lookat.y, 0,
			right_vector.z, up_vector.z, -lookat.z, 0,		//因为r_matrix已经考虑了-z轴的情况，lookat.z已经是负的了
			0, 0, 0, 1
		};
		view_and_projection.m_view = m_rotate_matrix * glm::transpose(T_view);
	}

	void Camera::CalculateViewMatrix2()
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
		view_and_projection.m_view = glm::transpose(R_view) * glm::transpose(T_view);//glsl是列为主
		//m_view_projection= m_projection  * m_view;
		
		r = std::sqrt(x * x + z * z + y * y);

	}

	void Camera::CalculateProjectionMatrix()
	{
		if (cameraType == ProjectionType::Orthographic) {
			float left = -m_aspectRatio * m_size;
			float right = m_aspectRatio * m_size;
			float top = m_size;
			float bottom = -m_size;

			view_and_projection.m_projection= glm::ortho(left, right, bottom, top, o_near, o_far);
		}
		else {
			view_and_projection.m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, p_near, p_far);
		}

	}

}