#pragma once

#include "Engine/EEpch.h"
#include <glm/glm.hpp>
#include "Entity.h"

namespace EE {

	using Entity = int;
	const Entity MAX_ENTITIES = 500;
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENT = 32;

	using Signature = std::bitset<MAX_COMPONENT>;

	class EntityManager
	{
	public:
		EntityManager();
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void SetSignature(Entity entity,Signature signature);
		Signature GetSignature(Entity entity);
		uint32_t GetLivingEntityCount() { return mLivingEntityCount; }
		std::vector<Entity> GetLivingEntities() { return mLivingEntities; }

	private:
		std::queue<Entity> mAvailableEntities{};
		std::vector<Entity> mLivingEntities;
		std::array<Signature, MAX_ENTITIES> mSignatures{};
		uint32_t mLivingEntityCount{};
	};

}


