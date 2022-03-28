#pragma once

#include "Engine/EEpch.h"
#include "Engine/Core/Timestep.h"
#include "Engine/ECS/Coordinator.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/ECS/System/RenderSystem.h"
#include "Engine/ECS/System/CameraControlSystem.h"
#include "Engine/ECS/Entity.h"
#include "Engine/Events/Event.h"

namespace EE {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void CreateEntity();
		void DestroyEntity(Entity enttity);
		template<typename T>
		void AddComponent(Entity entity, T component);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		Coordinator* GetCooptr() { return mCoo_ptr.get(); }

	private:
		std::unique_ptr<Coordinator> mCoo_ptr;		//一个Scene只有一个Coo
		std::vector<Entity> entities;
		Entity activeEntity;
		std::shared_ptr<RenderSystem> renderSys_ptr;
		std::shared_ptr<CameraControlSystem> cameraControlSys_ptr;
	};

}
