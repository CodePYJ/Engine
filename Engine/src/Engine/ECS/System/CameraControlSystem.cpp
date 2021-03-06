#include "CameraControlSystem.h"
#include "../Component/Components.h"


namespace EE {

	void CameraControlSystem::Init(Coordinator* coo_ptr)
	{
		SceneCoo_ptr = coo_ptr;
		Signature signature;
		signature.set(SceneCoo_ptr->GetComponentType<TransformComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<CameraComponent>());
		signature.set(SceneCoo_ptr->GetComponentType<TagComponent>());
		SceneCoo_ptr->SetSystemSignature<CameraControlSystem>(signature);

		camera_uniform_block = std::make_shared<UniformBuffer>(sizeof(glm::mat4) * 2);
		camera_uniform_block->SetBindPoint(0);
		camera_uniform_block->Unbind();
	}

	void CameraControlSystem::Update(Timestep ts, bool block)
	{
		if (activeCamera != -1) {
			CameraComponent& cameraC = SceneCoo_ptr->GetComponent<CameraComponent>(activeCamera);
			auto& camera = cameraC.cameraController->GetCamera();
			TransformComponent& trans = SceneCoo_ptr->GetComponent<TransformComponent>(activeCamera);
			cameraC.cameraController->SetPosition(trans.position);
			cameraC.cameraController->SetRotation(trans.rotation);
			cameraC.cameraController->OnUpdate(ts, block);
			trans.position = cameraC.cameraController->GetPosition();
			trans.rotation = cameraC.cameraController->GetRotation();

			camera_uniform_block->Bind();
			camera_uniform_block->SetData(0, sizeof(glm::mat4) * 2, &camera.GetViewAndProjectionStruct());
			camera_uniform_block->Unbind();

			//SceneCoo_ptr->msgEvent.SetMat4Msg(MsgType::CAMERA_MSG, camera.cameraController->GetCamera().GetViewProjectionMatrix());
		}
	}

	void CameraControlSystem::OnEvent(Event& event)
	{
		if (activeCamera != -1) {
			TransformComponent& trans = SceneCoo_ptr->GetComponent<TransformComponent>(activeCamera);
			CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(activeCamera);
			camera.cameraController->OnEvent(event);
			trans.position = camera.cameraController->GetPosition();
		}
	}

	void CameraControlSystem::SetActiveCamera(Entity camera)
	{
		activeCamera = camera;
	}
}