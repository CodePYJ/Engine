#include "Scene.h"
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

	void Scene::CreateEntity()
	{
		Entity entity = mCoo_ptr->CreateEntity();
		mCoo_ptr->AddComponent<TagComponent>(entity, {"entity"});
	}

	void Scene::DestroyEntity(Entity entity)
	{
		mCoo_ptr->DestroyEntity(entity);
	}

	template<typename T>
	void Scene::AddComponent(Entity entity, T component)
	{
		std::string typeName = typeid(T).name();
		mCoo_ptr->AddComponent<T>(entity, component);
		if (typename == "Renderable2D") {
			Renderer2D::RendererInit(&(mCoo_ptr->GetComponent<T>(entity).data));
		}
		if (typename == "Camera") {
			mCoo_ptr->GetComponent<T>(entity).cameraController = std::make_shared<OrthCameraController>(16.0f / 9.0f);
		}
	}

}