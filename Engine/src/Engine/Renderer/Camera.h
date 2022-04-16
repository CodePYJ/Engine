#pragma once

#include "Engine/EEpch.h"
#include "Engine/Core/Core.h"
#include <glm/glm.hpp>

namespace EE {

	class EE_API Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

		struct ViewAndProjection
		{
			glm::mat4 m_projection = glm::mat4(1.0f);
			glm::mat4 m_view = glm::mat4(1.0f);
		};

		Camera()  = default;

		void SetOrthographic(float size, float nearClip, float farClip) { m_size = size; o_near = nearClip; o_far = farClip; }
		void SetPerspective(float verticalFOV, float nearClip, float farClip) { m_fov = verticalFOV; p_near = nearClip; p_far = farClip; }

		float GetOrthographicSize() const { return m_size; }
		void SetOrthographicSize(float size) { m_size = size; CalculateProjectionMatrix(); }
		float GetOrthographicNearClip() const { return o_near; }
		void SetOrthographicNearClip(float nearClip) { o_near = nearClip; CalculateProjectionMatrix(); }
		float GetOrthographicFarClip() const { return o_far; }
		void SetOrthographicFarClip(float farClip) { o_far = farClip; CalculateProjectionMatrix(); }

		float GetPerspectiveVerticalFOV() const { return m_fov; }
		void SetPerspectiveVerticalFOV(float verticalFov) { m_fov = verticalFov; CalculateProjectionMatrix(); }
		float GetPerspectiveNearClip() const { return p_near; }
		void SetPerspectiveNearClip(float nearClip) { p_near = nearClip; CalculateProjectionMatrix(); }
		float GetPerspectiveFarClip() const { return p_far; }
		void SetPerspectiveFarClip(float farClip) { p_far = farClip; CalculateProjectionMatrix(); }

		glm::vec3 GetPosition() { return m_position; }
		void SetPosition(glm::vec3& position) { m_position = position; CalculateViewMatrix(); }
		glm::vec3 GetRotation() { return m_rotation; }
		void SetRotation(glm::vec3 rotation) { m_rotation = rotation; CalculateViewMatrix(); }
		float GetViewPort() { return m_aspectRatio; }
		void SetViewPort(float aspectRatio) { m_aspectRatio = aspectRatio; CalculateProjectionMatrix(); }
		ProjectionType GetProjectionType() { return cameraType; }
		void SetProjectionType(ProjectionType type) { cameraType = type; CalculateProjectionMatrix(); }

		void CalculateProjectionMatrix();
		glm::mat4 GetProjectionMatrix() { return view_and_projection.m_projection; }
		glm::mat4 GetViewMatrix() { return view_and_projection.m_view; }
		ViewAndProjection GetViewAndProjectionStruct() { return view_and_projection; }
		glm::vec3 GetFrontDirection();

		float GetR() { return r; }
	private:
		void CalculateViewMatrix();

	private:

		ViewAndProjection view_and_projection;
		glm::mat4 m_view_projection = glm::mat4(1.0f);
		glm::mat4 m_rotate_matrix = glm::mat4(1.0f);

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
		float m_aspectRatio = 0.0f;
		float m_size = 1.0f;
		float m_fov = 45.0f;
		float p_near = 0.01f, p_far = 1000.0f;	//perspective
		float o_near = 1.0f, o_far = -1.0f;	//orthographic
		ProjectionType cameraType = ProjectionType::Perspective;

		float r = 0.0f;
	};

}
