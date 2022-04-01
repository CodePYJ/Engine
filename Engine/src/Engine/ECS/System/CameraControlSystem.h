#pragma once

#include "../System.h"
#include "Engine/Renderer/CameraController.h"
#include "../Coordinator.h"
#include "Engine/Events/Event.h"
#include "../MsgEvent.h"


namespace EE {

	class CameraControlSystem: public System
	{
	public:
		void Init(Coordinator* coo_ptr);
		void Update(Timestep ts);
		void OnEvent(Event& event);
		void SetActiveCamera(Entity camera);
	private:
		Coordinator* SceneCoo_ptr;
		Entity activeCamera = -1;
	};

	class CameraMsgEvent : public MsgEvent
	{
	public:
		glm::mat4 ViewProjection;

	private:
		MsgType msgType = MsgType::CAMERA_MSG;
	};
}



