#include "Engine/EEpch.h"
#include "Render3DSystem.h"
#include "../Component/Components.h"
#include "../MsgEvent.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	void Render3DSystem::Init(Coordinator* coo_ptr)
	{
		SceneCoo_ptr = coo_ptr;
		Signature signature;
		signature.set(SceneCoo_ptr->GetComponentType<TransformComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<MeshComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<TagComponent>());
		SceneCoo_ptr->SetSystemSignature<Render3DSystem>(signature);

		//defer_shader = std::make_shared<Shader>("assets/shaders/gshader.shader");

		//FramebufferSpecification fbSpec;
		//fbSpec.Attachments = {
		//	{FramebufferTextureFormat::RGB16F, FramebufferTextureDataFormat::FLOAT},
		//	{FramebufferTextureFormat::RGB16F, FramebufferTextureDataFormat::FLOAT},
		//	{FramebufferTextureFormat::RGBA8, FramebufferTextureDataFormat::FLOAT},
		//	{FramebufferTextureFormat::Depth, FramebufferTextureDataFormat::None} };

		//m_framebuffer.SetFramebufferSpec(fbSpec);
		//m_framebuffer.Init();
	}

	void Render3DSystem::Update(Timestep ts)
	{
		//m_framebuffer.Bind();
		//defer_shader->Bind();
		for (Entity entity : mEntities)
		{
			auto& meshComponent = SceneCoo_ptr->GetComponent<MeshComponent>(entity);
			auto& model = meshComponent.model;
			auto& transform = SceneCoo_ptr->GetComponent<TransformComponent>(entity).GetTransform();
			if (model != nullptr) {
				model->Draw({ transform, meshComponent.color, entity,meshComponent.specularStrength, meshComponent.shininess });
			}
		}

	}

	void Render3DSystem::OnEvent(Event& event)
	{

	}
}