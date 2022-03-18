#include  <glad/glad.h>

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	struct Renderer2DStorage
	{
		std::unique_ptr<EE::VertexArray> VAO;
		std::unique_ptr<EE::Shader> shader;
		std::unique_ptr<EE::VertexBuffer> VBO;
		VertexBufferLayout layout;
		std::unique_ptr<EE::IndexBuffer> EBO;
	};

	static Renderer2DStorage* s_Data;

	Renderer2D::~Renderer2D()
	{
		Shutdown();
	}

	void Renderer2D::Init()
	{
		glEnable(GL_DEPTH_TEST);
		s_Data = new Renderer2DStorage();
		s_Data->VAO = std::make_unique<EE::VertexArray>();
		s_Data->VAO->Bind();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 1
		};

		s_Data->VBO = std::make_unique<EE::VertexBuffer>(vertices, sizeof(vertices));
		s_Data->layout.PushFloat(3);

		s_Data->EBO = std::make_unique<EE::IndexBuffer>(indices, 6);
		s_Data->VAO->AddBuffer(*(s_Data->VBO), s_Data->layout);
		s_Data->VAO->AddEBO(*(s_Data->EBO));
		s_Data->shader = std::make_unique<EE::Shader>("D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/test.shader");
		s_Data->shader->Bind();
		//texture = std::make_unique<EE::Texture>("D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/textures/ChernoLogo.png");
		s_Data->shader->SetUniformMat4("transform", glm::mat4(1.0f));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_Data->shader->Bind();
		s_Data->VAO->Bind();
		s_Data->shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	// Primitives
	void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), rotation, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const glm::vec4& color)
	{
		
		s_Data->shader->SetUniform4f("u_Color", color);
		glm::mat4 transform;
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
		s_Data->shader->SetUniformMat4("transform", transform);
		glDrawElements(GL_TRIANGLES, s_Data->EBO->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}