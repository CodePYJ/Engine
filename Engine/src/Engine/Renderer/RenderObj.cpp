#include "RenderObj.h"


namespace EE {

	RenderObj::RenderObj(float vers[36], std::string path)
		: vertices(vers), shaderPath(path)
	{
		VAO = std::make_unique<EE::VertexArray>();
		VAO->Bind();

		Init(vers, path);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 1
		};

		VBO = std::make_unique<EE::VertexBuffer>(vertices, sizeof(float)*36);
		layout.PushFloat(3);		//position
		layout.PushFloat(3);		//color
		layout.PushFloat(3);		//normal

		EBO = std::make_unique<EE::IndexBuffer>(indices, 6);
		VAO->AddBuffer(*(VBO), layout);
		VAO->AddEBO(*(EBO));
		shader = std::make_unique<EE::Shader>(shaderPath);
		shader->Bind();
		shader->SetUniformMat4("transform", glm::mat4(1.0f));
	}

	void RenderObj::Init(float vers[36], std::string path)
	{
		for (int i = 0; i < 4; i++) {
			position = { vers[i * 9 + 0], vers[i * 9 + 1], vers[i * 9 + 2] };
			color = { vers[i * 9 + 3], vers[i * 9 + 4], vers[i * 9 + 5], 1.0f};
			normal = { vers[i * 9 + 6], vers[i * 9 + 7], vers[i * 9 + 8] };
		}
		rotation = 0.0f;
		size = { 1.0f,1.0f ,1.0f };
	}

}