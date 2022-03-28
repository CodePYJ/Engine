#pragma once

#include "../System.h"
#include "Engine/Renderer/CameraController.h"
#include "../Coordinator.h"
#include "Engine/Events/Event.h"

namespace EE {

	class CameraControlSystem: public System
	{
	public:
		void Init(Coordinator* coo_ptr);
		void Update(Timestep ts);
		void OnEvent(Event& event);

	private:
		Coordinator* SceneCoo_ptr;
		Entity activeEntity;
	};
}



