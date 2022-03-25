#include "ComponentManager.h"

namespace EE {

	template<typename T>
	void ComponentManager::RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		EE_ASSERT(mComponentTypes.find(typeName) == mComponentTypes.end(), "Registering component type more than once.");
		mComponentTypes.insert({ typeName, mNextComponentType });
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
		++mNextComponentType;
	}

	template<typename T>
	ComponentType ComponentManager::GetComponentType()
	{
		const char* typeName = typeid(T).name();

		EE_ASSERT(mComponentTypes.find(typeName) != mComponentTypes.end(), "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return mComponentTypes[typeName];
	}

	template<typename T>
	void ComponentManager::AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void ComponentManager::RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& ComponentManager::GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void ComponentManager::EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}
}