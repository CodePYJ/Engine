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
			mCoo_ptr->AddComponent<T>(entity, component);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			mCoo_ptr->RemoveComponent<T>(entity);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return mCoo_ptr->GetComponent<T>(entity);
		}

		template<typename T>
		bool HasComponent(Entity entity)
		{
			return mCoo_ptr->HasComponent<T>(entity);
		}

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);
		void SetActiveCamera(Entity camera) 
		{ 
			activeCamera = camera;
			cameraControlSys_ptr->SetActiveCamera(camera);
		}
		Entity GetActiveCamera() { return activeCamera; }

		void SetAspectRatio(float w, float h) { viewPortAspectRatio = w / h; }
		float GetAspectRatio() { return viewPortAspectRatio; }

		Entity GetSelectedEntity() { return selectedEntity; }
		void SetSelectedEntity(Entity entity) { selectedEntity = entity; }

		Coordinator* GetCooptr() { return mCoo_ptr.get(); }
		
		std::vector<Entity> GetLivingEntities() { return mCoo_ptr->GetLivingEntities(); }

		void PushCamera(Entity entity) { cameras.push_back(entity); }
		void PopCamera(Entity entity) 
		{ 
			auto it = std::find(cameras.begin(), cameras.end(), entity);
			if (it != cameras.end())
				cameras.erase(it);
		}

		Entity GetRandomCamera()
		{
			if (cameras.empty())
				return -1;
			return cameras[0];
		}

	private:
		std::unique_ptr<Coordinator> mCoo_ptr;		//一个Scene只有一个Coo
		std::vector<Entity> entities;
		Entity activeCamera = -1;
		Entity selectedEntity = -1;
		std::shared_ptr<RenderSystem> renderSys_ptr;
		std::shared_ptr<CameraControlSystem> cameraControlSys_ptr;
		std::vector<Entity> cameras;
		float viewPortAspectRatio;
	};

}
