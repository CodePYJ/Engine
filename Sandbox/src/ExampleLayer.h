#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Camera.h"

class ExampleLayer : public EE::Layer
{
public:
	ExampleLayer();

	void OnUpdate(EE::Timestep timestep) override;
	void OnEvent(EE::Event& event) override;
	void OnImGuiRender() override;

private:
	EE::Renderer renderer;
	
	EE::OrthographicCamera m_Camera;

	glm::mat4 transform;
	float tran[2] = {0.0f, 0.0f};
	float tranX = 0.0f, tranY = 0.0f, rotation = 0.0f;
	float color[4] = {0.2f, 0.2f, 0.8f, 1.0f} ;
};