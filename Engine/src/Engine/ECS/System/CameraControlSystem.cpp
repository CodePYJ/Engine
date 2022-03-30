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

	void CameraControlSystem::Update(Timestep ts)
	{
		CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(activeCamera);
		TransformComponent& trans = SceneCoo_ptr->GetComponent<TransformComponent>(activeCamera);
		camera.cameraController->OnUpdate(ts);
		trans.position = camera.cameraController->GetPosition();
		trans.rotation.z = camera.cameraController->GetRotation();
		camera.cameraController->GetCamera().SetPosition(trans.position);
		camera.cameraController->GetCamera().SetRotation(trans.rotation.z);
		SceneCoo_ptr->msgEvent.SetMat4Msg(MsgType::CAMERA_MSG, camera.cameraController->GetCamera().GetViewProjectionMatrix());
	}

	void CameraControlSystem::OnEvent(Event& event)
	{
		CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(activeCamera);
		camera.cameraController->OnEvent(event);
	}

	void CameraControlSystem::SetActiveCamera(Entity camera)
	{
		activeCamera = camera;
	}
}