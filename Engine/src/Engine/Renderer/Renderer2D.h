#pragma once

#include <glm/glm.hpp>
#include "Camera.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Engine/ECS/Entity.h"


namespace EE {

	enum class Render2DType
	{
		NONE = 0, SQUARE = 1, CIRCLE = 2
	};

	struct QuardVertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
		glm::vec2 texCoord;
		int entityID;
	};

	struct CircleData
	{
		float vertices[32] = {
			-0.5f, -0.5f, 0.0f,  0.8f, 0.2f, 0.0f,  -1.0f, -1.0f,
			0.5f, -0.5f, 0.0f,   0.8f, 0.8f, 0.0f,	1.0f, -1.0f,
			-0.5f, 0.5f, 0.0f,   0.2f, 0.8f, 0.0f,	-1.0f, 1.0f,
			0.5f, 0.5f, 0.0f,     0.8f, 0.2f, 0.0f,	1.0f, 1.0f
		};
		glm::vec3 worldPosition;
		float thickness;
		glm::vec2 localPosition;
		unsigned int verSize = 32 * sizeof(float);
		unsigned int indices[6] = {
				0, 1, 2,
				2, 3, 1
		};
		unsigned int indCount = 6;
		std::string shaderPath = "assets/shaders/render2D_Circle.shader";
	};

	struct Light
	{
		float vertices[36] = {
			-0.2f, -0.2f, 0.0f,  0.8f, 0.2f, 0.0f,  -1.0f, -1.0f, 1.0f,
			0.2f, -0.2f, 0.0f,   0.8f, 0.8f, 0.0f,	1.0f, -1.0f, 1.0f,
			-0.2f, 0.2f, 0.0f,   0.2f, 0.8f, 0.0f,	-1.0f, 1.0f, 1.0f,
			0.2f, 0.2f, 0.0f,     0.8f, 0.2f, 0.0f,	1.0f, 1.0f, 1.0f
		};
		unsigned int verSize = 36 * sizeof(float);
		unsigned int indices[6] = {
				0, 1, 2,
				2, 3, 1
		};
		unsigned int indCount = 6;
		std::string shaderPath = "assets/shaders/test.shader";
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 2000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		std::shared_ptr<VertexArray> quad_VAO;
		std::shared_ptr<VertexBuffer> quad_VBO;
		std::shared_ptr<EE::Shader> quad_shader;
		VertexBufferLayout quad_layout;
		uint32_t quad_index_count = 0;
		QuardVertex* quad_vertex_base = nullptr;
		QuardVertex* quad_vertex_ptr = nullptr;

		glm::vec4 quad_vertex_position[4];
	};
	static Renderer2DData renderdata;

	class Renderer2D
	{
	public:
		static void RendererInit();
		static void Shutdown();

		static void BeginScene(Render2DType renderType, const glm::mat4& view_projection);
		static void EndScene();

		static void Flush();

		static void DrawQuad(const glm::mat4& transform, const glm::vec3& color, Entity entity);
	};
}
