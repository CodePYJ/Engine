#include "Scene.h"
//#include "Engine/Renderer/Renderer2D.h"
#include "Engine/ECS/Component/Components.h"


namespace EE {

	Scene::Scene()
	{
		mCoo_ptr = std::make_unique<Coordinator>();
		mCoo_ptr->Init();

		mCoo_ptr->RegisterComponent<Renderable2DComponent>();
		mCoo_ptr->RegisterComponent<MeshComponent>();
		mCoo_ptr->RegisterComponent<TransformComponent>();
		mCoo_ptr->RegisterComponent<CameraComponent>();
		mCoo_ptr->RegisterComponent<TagComponent>();

		render2DSys_ptr = mCoo_ptr->RegisterSystem<Render2DSystem>();
		render3DSys_ptr = mCoo_ptr->RegisterSystem<Render3DSystem>();
		render2DSys_ptr->Init(mCoo_ptr.get());
		render3DSys_ptr->Init(mCoo_ptr.get());
		cameraControlSys_ptr = mCoo_ptr->RegisterSystem<CameraControlSystem>();
		cameraControlSys_ptr->Init(mCoo_ptr.get());
	}

	Scene::~Scene()
	{
		
	}

	void Scene::OnUpdate(Timestep ts)
	{
		render2DSys_ptr->Update(ts);
		render3DSys_ptr->Update(ts);
		cameraControlSys_ptr->Update(ts, m_block);
	}

	void Scene::OnEvent(Event& event)
	{
		render2DSys_ptr->OnEvent(event);
		render3DSys_ptr->OnEvent(event);
		cameraControlSys_ptr->OnEvent(event);
	}

	Entity Scene::CreateEntity()
	{
		Entity entity = mCoo_ptr->CreateEntity();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		mCoo_ptr->DestroyEntity(entity);
	}

}