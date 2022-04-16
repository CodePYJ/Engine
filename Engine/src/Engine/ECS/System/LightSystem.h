#pragma once

#include "Engine.h"
#include "../System.h"
#include "Engine/ECS/Coordinator.h"
#include "Engine/Renderer/UniformBuffer.h"
#include "Engine/Renderer/Light.h"


namespace EE {

	class LightSystem :public System
	{
	public:
		void Init(Coordinator* coo_ptr);
		void Update(Timestep ts);
		void OnEvent(Event& event);

	private:
		bool playing = false;
		Coordinator* SceneCoo_ptr;
		Renderer renderer;
		unsigned int light_property_size = 128;
		std::shared_ptr<UniformBuffer> light_uniform_block;
	};
}