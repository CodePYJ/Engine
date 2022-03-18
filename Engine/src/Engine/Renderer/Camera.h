#pragma once

#include "Engine/EEpch.h";
#include "Engine/Core/Core.h"
#include <glm/glm.hpp>

namespace EE {

	class EE_API OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		glm::vec3 GetPosition() { return m_Position; }
		void SetPosition(glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }

		float GetRotation() { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

		void SetProjectionMatrix(float left, float right, float bottom, float top);
		glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		float m_Rotation = 0.0f;
	};


	class EE_API PerspectiveCamera
	{
	public:
		PerspectiveCamera(float left, float right, float bottom, float top);

		glm::vec3 GetPosition() { return m_Position; }
		void SetPosition(glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }

		float GetRotation() { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

		glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}
