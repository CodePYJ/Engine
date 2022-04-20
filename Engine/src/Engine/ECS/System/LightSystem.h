#pragma once

#include "Engine.h"
#include "../System.h"
#include "Engine/ECS/Coordinator.h"
#include "Engine/Renderer/Light.h"
#include "Engine/Renderer/UniformBuffer.h"


namespace EE {

	class LightSystem :public System
	{
	public:
		void Init(Coordinator* coo_ptr);
		void Update(Timestep ts);
		void OnEvent(Event& event);

	private:
		const uint32_t MaxLights = 32;
		bool playing = false;
		Coordinator* SceneCoo_ptr;
		Renderer renderer;
		std::shared_ptr<UniformBuffer>	light_uniform_block;
		unsigned int light_property_size = 96;
		int light_count = 0;
	};
}