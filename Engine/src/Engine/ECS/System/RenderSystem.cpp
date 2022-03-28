#include "RenderSystem.h"
#include "../Component/Components.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	void RenderSystem::Init(Coordinator* coo_ptr)
	{
		SceneCoo_ptr = coo_ptr;
		Signature signature;
		signature.set(SceneCoo_ptr->GetComponentType<TransformComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<Renderable2DComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<TagComponent>());
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

			if (!playing) {
				glm::mat4 transform;
				transform = glm::translate(glm::mat4(1.0f), transData.position);
				transform = glm::rotate(transform, glm::radians(transData.rotation.z), glm::vec3(0.0, 0.0, 1.0))
					* glm::scale(glm::mat4(1.0f), transData.scale);
				renderable.data_ptr->shader->SetUniformMat4("transform", transform);
			}
			glDrawElements(GL_TRIANGLES, renderable.data_ptr->EBO->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

	void RenderSystem::OnEvent(Event& event)
	{

	}
}