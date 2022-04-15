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
	}

	void Render3DSystem::Update(Timestep ts)
	{
		glm::mat4 view_projection = SceneCoo_ptr->msgEvent.getMat4Msg(MsgType::CAMERA_MSG);
		for (Entity entity : mEntities)
		{
			auto& meshComponent = SceneCoo_ptr->GetComponent<MeshComponent>(entity);
			auto& model = meshComponent.model;
			auto& transform = SceneCoo_ptr->GetComponent<TransformComponent>(entity).GetTransform();
			if (model != nullptr) {
				model->Draw({ view_projection, transform, meshComponent.color, entity});
			}
		}

	}

	void Render3DSystem::OnEvent(Event& event)
	{

	}
}