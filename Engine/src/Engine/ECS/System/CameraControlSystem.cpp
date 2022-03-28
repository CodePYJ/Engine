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

	}

	void CameraControlSystem::Update(Timestep ts)
	{
		for (Entity entity : mEntities) {
			CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(entity);
			camera.cameraController->OnUpdate(ts);

		}
	}

	void CameraControlSystem::OnEvent(Event& event)
	{
		for (Entity entity : mEntities) {
			CameraComponent& camera = SceneCoo_ptr->GetComponent<CameraComponent>(entity);
			camera.cameraController->OnEvent(event);

		}
	}


}