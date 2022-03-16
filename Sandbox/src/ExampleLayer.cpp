#include "Engine.h"

#include "ExampleLayer.h"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	float vertices[] = {
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,    0.2f, 0.5f, 0.8f,
			0.5f, -0.5f, 0.0f,    1.0f, 0.0f,    0.2f, 0.5f, 0.8f,
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f,    0.2f, 0.5f, 0.8f,
			0.5f, 0.5f, 0.0f,      1.0f, 1.0f,    0.2f, 0.5f, 0.8f
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
	layout.PushFloat(3);
	vao->AddBuffer(*vbo, layout);
	shader->Bind();
	texture->Bind();
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
	shader->SetUniformMat4("transform", glm::mat4(1.0f));
	shader->SetUniform4f("u_Color", glm::vec4(0.2, 0.5, 0.9, 1.0));
}

void ExampleLayer::OnUpdate(EE::Timestep timestep)
{
	//EE_TRACE(timestep.GetSecond());
	renderer.Clear();
	renderer.Draw(*vao, *ebo, *shader);
}

void ExampleLayer::OnEvent(EE::Event& event)
{
	//EE_INFO("Example Event");
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("test");
	ImGui::SliderFloat3("position", tran, -1.0f, 1.0f);
	ImGui::SliderFloat("rotation", &rotation, 0.0f, 360.0f);
	ImGui::ColorEdit4("color", color);
	ImGui::End();
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(tran[0], tran[1], 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
	shader->SetUniformMat4("transform", transform);
	shader->SetUniform4f("u_Color", glm::vec4(color[0], color[1], color[2], color[3]));
}