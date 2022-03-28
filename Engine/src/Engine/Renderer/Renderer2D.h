#pragma once

#include <glm/glm.hpp>
#include "Camera.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


namespace EE {

	struct Renderer2DData
	{
		std::unique_ptr<EE::VertexArray> VAO;
		std::unique_ptr<EE::Shader> shader;
		std::unique_ptr<EE::IndexBuffer> EBO;
		std::unique_ptr<EE::VertexBuffer> VBO;
		VertexBufferLayout layout;

		float* vertices;
		unsigned int verSize;
		float* indices;
		unsigned int indCount;
		std::string shaderPath;
	};

	class Renderer2D
	{
	public:
		static void RendererInit(Renderer2DData* renderdata);

		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(glm::vec3 lightPos);

	private:

	};
}
