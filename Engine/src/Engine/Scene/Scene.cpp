#include "Scene.h"
//#include "Engine/Renderer/Renderer2D.h"
#include "Engine/ECS/Component/Components.h"


namespace EE {

	Scene::Scene()
	{
		mCoo_ptr = std::make_unique<Coordinator>();
		mCoo_ptr->Init();

		mCoo_ptr->RegisterComponent<Renderable2DComponent>();
		mCoo_ptr->RegisterComponent<TransformComponent>();
		mCoo_ptr->RegisterComponent<CameraComponent>();
		mCoo_ptr->RegisterComponent<TagComponent>();

		renderSys_ptr = mCoo_ptr->RegisterSystem<RenderSystem>();
		renderSys_ptr->Init(mCoo_ptr.get());
		cameraControlSys_ptr = mCoo_ptr->RegisterSystem<CameraControlSystem>();
		cameraControlSys_ptr->Init(mCoo_ptr.get());
	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(Timestep ts)
	{
		renderSys_ptr->Update(ts);
		cameraControlSys_ptr->Update(ts);
	}

	void Scene::OnEvent(Event& event)
	{
		renderSys_ptr->OnEvent(event);
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