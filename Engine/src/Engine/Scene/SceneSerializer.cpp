#include "SceneSerializer.h"

#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Component/Components.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/CameraController.h"
#include "Engine/Renderer/Renderer2D.h"

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace EE {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& scenePtr)
		:m_ScenePtr(scenePtr)
	{

	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		std::vector<Entity> LivingEntities = m_ScenePtr->GetLivingEntities();
		for(Entity entity : LivingEntities)
		{
			SerializeEntity(out, entity);
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{

	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << entity; // TODO: Entity ID goes here

		if (m_ScenePtr->HasComponent<TagComponent>(entity))
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = m_ScenePtr->GetComponent<TagComponent>(entity).tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent
		}

		if (m_ScenePtr->HasComponent<TransformComponent>(entity))
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = m_ScenePtr->GetComponent<TransformComponent>(entity);
			out << YAML::Key << "Position" << YAML::Value << tc.position;
			out << YAML::Key << "Rotation" << YAML::Value << tc.rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.scale;

			out << YAML::EndMap; // TransformComponent
		}

		if (m_ScenePtr->HasComponent<CameraComponent>(entity))
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = m_ScenePtr->GetComponent<CameraComponent>(entity);
			auto& camera = cameraComponent.cameraController;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera->GetCameraType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera->GetPerspFov();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera->GetPerspNear();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera->GetPerspFar();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera->GetOrthoSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera->GetOrthoNear();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera->GetOrthoFar();
			out << YAML::EndMap; // Camera

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.primary;
			//out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

			out << YAML::EndMap; // CameraComponent
		}

		if (m_ScenePtr->HasComponent<Renderable2DComponent>(entity))
		{
			out << YAML::Key << "Renderable2DComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& renderable = m_ScenePtr->GetComponent<Renderable2DComponent>(entity);
			out << YAML::Key << "Color" << YAML::Value << renderable.color;
			out << YAML::Key << "Type" << YAML::Value << (int)renderable.type;

			out << YAML::EndMap; // TransformComponent
		}
		out << YAML::EndMap; // Entity
	}


	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto yaml_entity : entities)
			{
				uint64_t uuid = yaml_entity["Entity"].as<uint64_t>(); // TODO
				Entity deserializedEntity = m_ScenePtr->CreateEntity();

				std::string tag;
				auto tagComponent = yaml_entity["TagComponent"];
				if (tagComponent) {
					tag = tagComponent["Tag"].as<std::string>();
					m_ScenePtr->AddComponent<TagComponent>(deserializedEntity, { tag });
				}

				auto transformComponent = yaml_entity["TransformComponent"];
				if (transformComponent)
				{
					// Entities always have transforms
					glm::vec3 position = transformComponent["Position"].as<glm::vec3>();
					glm::vec3 rotation = transformComponent["Rotation"].as<glm::vec3>();
					glm::vec3 scale = transformComponent["Scale"].as<glm::vec3>();
					m_ScenePtr->AddComponent<TransformComponent>(deserializedEntity, { position, rotation, scale });
				}

				auto cameraComponent = yaml_entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cameraProps = cameraComponent["Camera"];
					std::shared_ptr<CameraController> cameraController = std::make_shared<CameraController>(m_ScenePtr->GetAspectRatio());

					cameraController->SetCameraType((Camera::ProjectionType)cameraProps["ProjectionType"].as<int>());

					cameraController->SetPerspFov(cameraProps["PerspectiveFOV"].as<float>());
					cameraController->SetPerspNear(cameraProps["PerspectiveNear"].as<float>());
					cameraController->SetPerspFar(cameraProps["PerspectiveFar"].as<float>());

					cameraController->SetOrthoSize(cameraProps["OrthographicSize"].as<float>());
					cameraController->SetOrthoNear(cameraProps["OrthographicNear"].as<float>());
					cameraController->SetOrthoFar(cameraProps["OrthographicFar"].as<float>());

					bool primary = cameraComponent["Primary"].as<bool>();
					//cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();

					m_ScenePtr->AddComponent<CameraComponent>(deserializedEntity,
						{
							cameraController,
							glm::mat4(1.0f),
							glm::mat4(1.0f),
							primary
						});
					if (primary)
						m_ScenePtr->SetActiveCamera(deserializedEntity);
				}//camera

				auto renderableComponent = yaml_entity["Renderable2DComponent"];
				if (renderableComponent) {
					glm::vec3 color = renderableComponent["Color"].as<glm::vec3>();
					//int type = renderableComponent["Type"].as<int>();
					m_ScenePtr->AddComponent<Renderable2DComponent>(deserializedEntity,
						{
							color,
							Render2DType::SQUARE
						});
				}
			}//for
		}
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		return false;
	}
}