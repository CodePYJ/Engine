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

		Entity CreateEntity();
		void DestroyEntity(Entity enttity);

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			//std::string typeName = typeid(T).name();
			mCoo_ptr->AddComponent<T>(entity, component);
			//if (typeName == "Renderable2DComponent") {
			//	Renderer2D::RendererInit(mCoo_ptr->GetComponent<Renderable2DComponent>(entity).data_ptr);
			//}
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return mCoo_ptr->GetComponent<T>(entity);
		}

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);
		void SetActiveCamera(Entity camera) 
		{ 
			activeCamera = camera;
			cameraControlSys_ptr->SetActiveCamera(camera);
		}
		Entity GetActiveCamera() { return activeCamera; }

		Coordinator* GetCooptr() { return mCoo_ptr.get(); }

	private:
		std::unique_ptr<Coordinator> mCoo_ptr;		//一个Scene只有一个Coo
		std::vector<Entity> entities;
		Entity activeCamera;
		std::shared_ptr<RenderSystem> renderSys_ptr;
		std::shared_ptr<CameraControlSystem> cameraControlSys_ptr;
	};

}
