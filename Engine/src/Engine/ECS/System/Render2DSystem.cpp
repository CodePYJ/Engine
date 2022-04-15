#include "Engine/EEpch.h"
#include "Render2DSystem.h"
#include "../Component/Components.h"
#include "../MsgEvent.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/quaternion.hpp>

namespace EE {

	void Render2DSystem::Init(Coordinator* coo_ptr)
	{
		SceneCoo_ptr = coo_ptr;
		Signature signature;
		signature.set(SceneCoo_ptr->GetComponentType<TransformComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<Renderable2DComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<TagComponent>());
		SceneCoo_ptr->SetSystemSignature<Render2DSystem>(signature);

	}

	void Render2DSystem::Update(Timestep ts)
	{
		//renderer.Clear();

		glm::mat4 view_projection = SceneCoo_ptr->msgEvent.getMat4Msg(MsgType::CAMERA_MSG);
		Renderer2D::BeginScene(Render2DType::SQUARE, view_projection);
		for (Entity entity : mEntities)
		{
			Renderable2DComponent& renderable = SceneCoo_ptr->GetComponent<Renderable2DComponent>(entity);
			TransformComponent& transData = SceneCoo_ptr->GetComponent<TransformComponent>(entity);
			
			if (renderable.type == Render2DType::SQUARE) {
				Renderer2D::DrawQuad(transData.GetTransform(), renderable.color, entity, renderable.texture);
			}
		}
		Renderer2D::Flush();
		Renderer2D::EndScene();
	}

	void Render2DSystem::OnEvent(Event& event)
	{

	}
}