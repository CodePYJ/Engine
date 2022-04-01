#pragma once

#include <glm/glm.hpp>
#include "Camera.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


namespace EE {

	class Renderer2DData
	{
	public:
		Renderer2DData();

		std::unique_ptr<EE::VertexArray> VAO;
		std::unique_ptr<EE::Shader> shader;
		std::unique_ptr<EE::IndexBuffer> EBO;
		std::unique_ptr<EE::VertexBuffer> VBO;
		VertexBufferLayout layout;

		float vertices[36] = {
			-0.2f, -0.2f, 0.0f,  0.8f, 0.8f, 0.0f,  -1.0f, -1.0f, 1.0f,
			0.2f, -0.2f, 0.0f,   0.8f, 0.8f, 0.0f,	1.0f, -1.0f, 1.0f,
			-0.2f, 0.2f, 0.0f,   0.8f, 0.8f, 0.0f,	-1.0f, 1.0f, 1.0f,
			0.2f, 0.2f, 0.0f,     0.8f, 0.8f, 0.0f,	1.0f, 1.0f, 1.0f
		};
		unsigned int verSize = 36 * sizeof(float);
		unsigned int indices[6] = {
				0, 1, 2,
				2, 3, 1
		};
		unsigned int indCount = 6;
		std::string shaderPath = "assets/shaders/test.shader";
	};

	class Renderer2D
	{
	public:
		static void RendererInit(std::shared_ptr<Renderer2DData> renderdata);

		static void Shutdown();

		static void BeginScene(Camera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(glm::vec3 lightPos);

	private:

	};
}
