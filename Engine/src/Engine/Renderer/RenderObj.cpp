#include "RenderObj.h"


namespace EE {

	RenderObj::RenderObj(std::string path)
		:shaderPath(path)
	{
		VAO = std::make_unique<EE::VertexArray>();
		VAO->Bind();

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

		VBO = std::make_unique<EE::VertexBuffer>(vertices, sizeof(vertices));
		layout.PushFloat(3);

		EBO = std::make_unique<EE::IndexBuffer>(indices, 6);
		VAO->AddBuffer(*(VBO), layout);
		VAO->AddEBO(*(EBO));
		shader = std::make_unique<EE::Shader>(shaderPath);
		shader->Bind();
		shader->SetUniformMat4("transform", glm::mat4(1.0f));
	}
}