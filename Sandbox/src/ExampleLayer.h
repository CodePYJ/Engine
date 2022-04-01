#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Renderer/CameraController.h"
#include "Engine/Renderer/RenderObj.h"
#include "Engine/Renderer/Framebuffer.h"

struct ObjVector
{
	std::string name;
	bool is_selected = false;
	int objID;
};

class ExampleLayer : public EE::Layer
{
public:
	ExampleLayer();
	~ExampleLayer();
	void OnUpdate(EE::Timestep timestep) override;
	void OnEvent(EE::Event& event) override;
	void OnImGuiRender() override;

private:
	void OnKeyPressedEvent(EE::KeyPressedEvent event);
	void OnMouseMovedEvent(EE::Event& event);
	void Reset();
	void CreatQuadImGui();

private:
	EE::Renderer renderer;
	EE::Framebuffer m_Framebuffer;
	EE::CameraController CameraController;

	glm::vec2 viewportSize = {0.0f, 0.0f};

	glm::mat4 transform;
	float pos[3] = {0.0f, 0.0f, 0.0f};
	float tranX = 0.0f, tranY = 0.0f, rotation = 0.0f;
	float color[4] = {0.2f, 0.2f, 0.8f, 1.0f};
	std::vector<std::string> objNames;
	float size[2] = {1.0f, 1.0f};

	std::string shaderPath[2] = { "D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/light.shader",
													 "D:/WorkSpace/CppWorkSpace/Engine/Engine/Engine/res/shaders/obj.shader" };
	int currentShader = 0;
	float vertices2D[36] = {
		-0.2f, -0.2f, 0.0f,  0.8f, 0.8f, 0.8f,  -1.0f, -1.0f, 1.0f,
		0.2f, -0.2f, 0.0f,   0.8f, 0.8f, 0.8f,	1.0f, -1.0f, 1.0f,
		-0.2f, 0.2f, 0.0f,   0.8f, 0.8f, 0.8f,	-1.0f, 1.0f, 1.0f,
		0.2f, 0.2f, 0.0f,     0.8f, 0.8f, 0.8f,	1.0f, 1.0f, 1.0f
	};
	glm::vec3 lightPos;

	EE::RenderObj* selectedObj = nullptr;
	int lastID = -1;

	bool m_ViewportFocused = false, m_ViewportHovered = false;
};