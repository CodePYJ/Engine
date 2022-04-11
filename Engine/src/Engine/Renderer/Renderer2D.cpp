#include "Renderer2D.h"
#include  <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	void Renderer2D::RendererInit()
	{
		renderdata.quad_VAO = std::make_shared<VertexArray>();
		renderdata.quad_VBO = std::make_shared<VertexBuffer>(renderdata.MaxVertices*sizeof(QuardVertex));

		renderdata.quad_layout.PushFloat(3);	//position;
		renderdata.quad_layout.PushFloat(3);	//color;
		renderdata.quad_layout.PushFloat(3);	//normal;
		renderdata.quad_layout.PushFloat(2);	//TexCoord;
		renderdata.quad_layout.PushInt(1);	//entityID;
		renderdata.quad_VAO->AddBuffer(*renderdata.quad_VBO, renderdata.quad_layout);
		renderdata.quad_vertex_base = new QuardVertex[renderdata.MaxVertices];
		uint32_t* quad_indices = new uint32_t[renderdata.MaxIndices];
		uint32_t offect = 0;
		for (int i = 0; i < renderdata.MaxIndices; i += 6) {
			quad_indices[i + 0] = offect + 0;
			quad_indices[i + 1] = offect + 1;
			quad_indices[i + 2] = offect + 2;

			quad_indices[i + 3] = offect + 2;
			quad_indices[i + 4] = offect + 3;
			quad_indices[i + 5] = offect + 1;
			offect += 4;
		}
		std::shared_ptr<IndexBuffer> EBO = std::make_shared<IndexBuffer>(quad_indices, renderdata.MaxIndices);
		renderdata.quad_VAO->AddEBO(EBO);
		renderdata.quad_shader = std::make_shared<Shader>("assets/shaders/test.shader");
		delete[] quad_indices;

		renderdata.quad_vertex_position[0] = { -0.5f, -0.5f, 0.0f,1.0f };
		renderdata.quad_vertex_position[1] = { 0.5f, -0.5f, 0.0f,1.0f };
		renderdata.quad_vertex_position[2] = { -0.5f, 0.5f, 0.0f,1.0f };
		renderdata.quad_vertex_position[3] = { 0.5f, 0.5f, 0.0f, 1.0f };
	}

	static void RendererSquareInit(std::shared_ptr<Renderer2DData> renderdata)
	{

	}

	static void RendererCircleInit(std::shared_ptr<Renderer2DData> renderdata)
	{

	}

	void Renderer2D::Shutdown()
	{
		delete[] renderdata.quad_vertex_base;
	}

	void Renderer2D::BeginScene(Render2DType type, const glm::mat4& view_projection)
	{	
		if (type == Render2DType::SQUARE) {
			renderdata.quad_index_count = 0;
			renderdata.quad_vertex_ptr = renderdata.quad_vertex_base;
			renderdata.quad_shader->Bind();
			renderdata.quad_shader->SetUniformMat4("u_ViewProjection", view_projection);
		}
		else if (type == Render2DType::CIRCLE)
		{

		}
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::Flush()
	{
		renderdata.quad_VAO->Bind();
		uint32_t data_size = (uint32_t)((uint8_t*)renderdata.quad_vertex_ptr - (uint8_t*)renderdata.quad_vertex_base);
		renderdata.quad_VBO->SetData(renderdata.quad_vertex_base, data_size);
		glDrawElements(GL_TRIANGLES, renderdata.quad_index_count, GL_UNSIGNED_INT, nullptr);
	}


	// Primitives

	void Renderer2D::DrawQuad(const glm::mat4& transform , const glm::vec3& color, Entity entity)
	{
		int quad_vertex_count = 4;
		for (int i = 0; i < quad_vertex_count; i++) {
			renderdata.quad_vertex_ptr->position = transform * renderdata.quad_vertex_position[i];
			renderdata.quad_vertex_ptr->color = color;
			renderdata.quad_vertex_ptr->entityID = entity;
			renderdata.quad_vertex_ptr++;
		}
		renderdata.quad_index_count += 6;

	}
}