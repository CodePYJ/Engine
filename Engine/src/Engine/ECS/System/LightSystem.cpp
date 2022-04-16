#include "Engine/EEpch.h"
#include "LightSystem.h"
#include "../Component/Components.h"
#include "../MsgEvent.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	void LightSystem::Init(Coordinator* coo_ptr)
	{
		SceneCoo_ptr = coo_ptr;
		Signature signature;
		signature.set(SceneCoo_ptr->GetComponentType<TransformComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<LightComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<TagComponent>());
		SceneCoo_ptr->SetSystemSignature<LightSystem>(signature);

		light_uniform_block = std::make_shared<UniformBuffer>(light_property_size);
		light_uniform_block->SetBindPoint(1);
		light_uniform_block->Unbind();
	}

	void LightSystem::Update(Timestep ts)
	{
		//glm::mat4 view_projection = SceneCoo_ptr->msgEvent.getMat4Msg(MsgType::CAMERA_MSG);
		for (Entity entity : mEntities)
		{
			auto& lightComponent = SceneCoo_ptr->GetComponent<LightComponent>(entity);
			auto& transformComponent = SceneCoo_ptr->GetComponent<TransformComponent>(entity);

			auto& light_model = lightComponent.light->GetLight();
			auto& transform = transformComponent.GetTransform();

			light_model.Draw({ transform,{1.0,1.0,1.0} , entity });//lightComponent.light_property.lightColor

			lightComponent.light->SetLightProperty({
					lightComponent.light_property.ambientStrength,
					lightComponent.light_property.specularStrength,
					lightComponent.light_property.specularIndex,
					lightComponent.light_property.lightColor,
					transformComponent.position
				});
			light_uniform_block->Bind();
			light_uniform_block->SetData(light_property_size, &lightComponent.light->light_property_mat4);
			light_uniform_block->Unbind();
		}

	}

	void LightSystem::OnEvent(Event& event)
	{

	}
}