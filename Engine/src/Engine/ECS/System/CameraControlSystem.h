#pragma once

#include "Engine/EEpch.h"
#include "../System.h"
#include "Engine/Renderer/CameraController.h"
#include "../Coordinator.h"
#include "../MsgEvent.h"
#include "Engine/Events/Event.h"
#include "Engine/Renderer/UniformBuffer.h"


namespace EE {

	class CameraControlSystem: public System
	{
	public:
		void Init(Coordinator* coo_ptr);
		void Update(Timestep ts, bool block);
		void OnEvent(Event& event);
		void SetActiveCamera(Entity camera);

	private:
		Coordinator* SceneCoo_ptr;
		Entity activeCamera = -1;
		std::shared_ptr<UniformBuffer> camera_uniform_block;
	};

	class CameraMsgEvent : public MsgEvent
	{
	public:
		glm::mat4 ViewProjection;

	private:
		MsgType msgType = MsgType::CAMERA_MSG;
	};
}



