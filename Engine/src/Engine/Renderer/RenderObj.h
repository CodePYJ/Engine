#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


namespace EE {

	class RenderObj
	{
	public:
		RenderObj(float vers[36], std::string path);
		void Init(float vers[36], std::string path);

		glm::vec3 GetPosition() { return position; }
		glm::vec4 GetColor() { return color; }
		float GetRotation() { return rotation; }
		glm::vec3 GetSize() { return size; }

		void SetPosition(glm::vec3 pos) { position = pos; }
		void SetRotation(float rot) { rotation = rot; }
		void SetColor(glm::vec4 co) { color = co; }
		void SetSize(glm::vec3 sz) { size = sz; }

		bool isLight() { return is_light; }

	public:
		std::unique_ptr<EE::VertexArray> VAO;
		std::unique_ptr<EE::Shader> shader;
		std::unique_ptr<EE::IndexBuffer> EBO;
		bool is_light = false;

	private:
		std::unique_ptr<EE::VertexBuffer> VBO;
		VertexBufferLayout layout;
		
		float* vertices;
		std::string shaderPath;
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		float rotation;
		glm::vec3 size;
	};
}
