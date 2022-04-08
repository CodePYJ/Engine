#pragma once

#include "Scene.h"
#include <fstream>

#include <yaml-cpp/yaml.h>

namespace EE {

	class SceneSerializer
	{
	public:
		SceneSerializer(const std::shared_ptr<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);
		void SerializeEntity(YAML::Emitter& out, Entity entity);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		std::shared_ptr<Scene> m_ScenePtr;
	};
}
