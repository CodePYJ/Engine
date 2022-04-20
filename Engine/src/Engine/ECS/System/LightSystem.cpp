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

		light_uniform_block = std::make_shared<UniformBuffer>(light_property_size*32+16);
		light_uniform_block->SetBindPoint(1);
		light_uniform_block->Unbind();
	}

	void LightSystem::Update(Timestep ts)
	{
		int i = 0;
		light_count = mEntities.size();
		light_uniform_block->Bind();
		light_uniform_block->SetData(0, 4, &light_count);
		for (Entity entity : mEntities)
		{
			auto& lightComponent = SceneCoo_ptr->GetComponent<LightComponent>(entity);
			auto& transformComponent = SceneCoo_ptr->GetComponent<TransformComponent>(entity);

			auto& light_property = lightComponent.light_property;
			auto& light_model = lightComponent.light->GetLight();
			auto& transform = transformComponent.GetTransform();

			light_uniform_block->SetData(i * light_property_size + 16, 4, &light_property.light_type);
			light_uniform_block->SetData(i * light_property_size + 20, 4, &light_property.ambientStrength);
			light_uniform_block->SetData(i * light_property_size + 32, 12, &light_property.lightColor);
			light_uniform_block->SetData(i * light_property_size + 48, 12, &transformComponent.position);
			light_uniform_block->SetData(i * light_property_size + 64, 12, &light_property.parallel_direction);
			light_uniform_block->SetData(i * light_property_size + 76, 4, &light_property.constant);
			light_uniform_block->SetData(i * light_property_size + 80, 4, &light_property.linear);
			light_uniform_block->SetData(i * light_property_size + 84, 4, &light_property.quadratic);
			light_uniform_block->SetData(i * light_property_size + 88, 4, &light_property.inner_cutoff);
			light_uniform_block->SetData(i * light_property_size + 92, 4, &light_property.outer_cutoff);
			light_uniform_block->SetData(i * light_property_size + 96, 16, &light_property.spot_direction);

			light_model.DrawLight({ transform, lightComponent.light_property.lightColor, entity });
			i++;
		}
		light_uniform_block->Unbind();
	}

	void LightSystem::OnEvent(Event& event)
	{

	}
}

/*
			lightComponent.light->SetLightProperty({
					lightComponent.light_property.ambientStrength,
					lightComponent.light_property.lightColor,
					transformComponent.position,
					lightComponent.light_property.light_type
				});

*/