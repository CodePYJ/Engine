#pragma once

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
public:
	ExampleLayer();

	void OnUpdate(EE::Timestep timestep) override;
	void OnEvent(EE::Event& event) override;
	void OnImGuiRender() override;

private:
	std::unique_ptr<EE::VertexBuffer> vbo;
	std::unique_ptr<EE::Shader> shader;
	std::unique_ptr<EE::VertexArray> vao;
	std::unique_ptr<EE::IndexBuffer> ebo;
	std::unique_ptr<EE::Texture> texture;
	EE::Renderer renderer;
	EE::VertexBufferLayout layout;
	EE::OrthographicCamera m_Camera;

	glm::mat4 transform;
	float tran[2] = {0.0f, 0.0f};
	float tranX = 0.0f, tranY = 0.0f, rotation = 0.0f;
	float color[4] = {0.2f, 0.5f, 0.8f, 1.0f} ;
};