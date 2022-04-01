#include "Engine/EEpch.h"
#include "RenderSystem.h"
#include "../Component/Components.h"
#include "../MsgEvent.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace EE {

	void RenderSystem::Init(Coordinator* coo_ptr)
	{
		SceneCoo_ptr = coo_ptr;
		Signature signature;
		signature.set(SceneCoo_ptr->GetComponentType<TransformComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<Renderable2DComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<TagComponent>());
		SceneCoo_ptr->SetSystemSignature<RenderSystem>(signature);
	}

	void RenderSystem::Update(Timestep ts)
	{
		renderer.Clear();

		for (Entity entity : mEntities)
		{
			auto& renderable = SceneCoo_ptr->GetComponent<Renderable2DComponent>(entity);
			auto& transData = SceneCoo_ptr->GetComponent<TransformComponent>(entity);
			
			renderable.data_ptr->VAO->Bind();
			renderable.data_ptr->shader->Bind();
			renderable.ViewProjection = SceneCoo_ptr->msgEvent.getMat4Msg(MsgType::CAMERA_MSG);

			if (!playing) {
				renderable.data_ptr->shader->SetUniformMat4("transform", transData.GetTransform());
				renderable.data_ptr->shader->SetUniform3f("u_color", renderable.color);
				renderable.data_ptr->shader->SetUniformMat4("u_ViewProjection", renderable.ViewProjection);
			}
			glDrawElements(GL_TRIANGLES, renderable.data_ptr->EBO->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

	void RenderSystem::OnEvent(Event& event)
	{

	}
}