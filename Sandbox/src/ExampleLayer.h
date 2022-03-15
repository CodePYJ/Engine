#pragma once

#include "Engine.h"

#include "Engine/Renderer/VertexBuffer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/IndexBuffer.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/VertexBufferLayout.h"
#include "Engine/Renderer/Camera.h"

class ExampleLayer : public EE::Layer
{
private:
	std::unique_ptr<EE::VertexBuffer> vbo;
	std::unique_ptr<EE::Shader> shader;
	std::unique_ptr<EE::VertexArray> vao;
	std::unique_ptr<EE::IndexBuffer> ebo;
	std::unique_ptr<EE::Texture> texture;
	EE::Renderer renderer;
	EE::VertexBufferLayout layout;
	EE::OrthographicCamera m_Camera;

public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 1
		};

		vao = std::make_unique<EE::VertexArray>();
		vbo = std::make_unique<EE::VertexBuffer>(vertices, sizeof(vertices));
		ebo = std::make_unique<EE::IndexBuffer>(indices, 6);
		shader = std::make_unique<EE::Shader>("D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/test.shader");
		texture = std::make_unique<EE::Texture>("D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/textures/ChernoLogo.png");

		layout.PushFloat(3);
		layout.PushFloat(2);
		vao->AddBuffer(*vbo, layout);
		shader->Bind();
		texture->Bind();
		shader->SetUniform1i("u_Texture", 0);
		shader->SetUniformMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
	}

	void OnUpdate(EE::Timestep timestep) override
	{
		EE_TRACE(timestep.GetSecond());
		renderer.Clear();
		renderer.Draw(*vao, *ebo, *shader);
	}

	void OnEvent(EE::Event& event) override
	{
		EE_INFO("Example Event");
	}
};