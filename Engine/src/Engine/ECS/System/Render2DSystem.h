#pragma once

#include "Engine.h"
#include "../System.h"
#include "Engine/ECS/Coordinator.h"

namespace EE {

	class Render2DSystem: public System
	{
	public:
		void Init(Coordinator* coo_ptr);
		void Update(Timestep ts);
		void OnEvent(Event& event);

	private:
		bool playing = false;
		Coordinator* SceneCoo_ptr;
		Renderer renderer;
	};

}