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
	}

	void CameraControlSystem::Update(Timestep ts, bool block)
	{
		if (activeCamera != -1) {
			CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(activeCamera);
			TransformComponent& trans = SceneCoo_ptr->GetComponent<TransformComponent>(activeCamera);
			camera.cameraController->SetPosition(trans.position);
			camera.cameraController->SetRotation(trans.rotation);
			camera.cameraController->OnUpdate(ts, block);
			trans.position = camera.cameraController->GetPosition();
			trans.rotation = camera.cameraController->GetRotation();

			SceneCoo_ptr->msgEvent.SetMat4Msg(MsgType::CAMERA_MSG, camera.cameraController->GetCamera().GetViewProjectionMatrix());
		}
	}

	void CameraControlSystem::OnEvent(Event& event)
	{
		if (activeCamera != -1) {
			CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(activeCamera);
			camera.cameraController->OnEvent(event);
		}
	}

	void CameraControlSystem::SetActiveCamera(Entity camera)
	{
		activeCamera = camera;
	}
}