#pragma once

#include "Engine/EEpch.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/CameraController.h"
#include "Engine/Renderer/Model.h"


namespace EE {

	struct TransformComponent
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::mat4 GetTransform() {
			glm::mat4 transform;
			transform = glm::translate(glm::mat4(1.0f), position);
			transform *= glm::toMat4(glm::quat(rotation));
			transform *= glm::scale(glm::mat4(1.0f), scale);
			return transform;
		}
	};

	struct Renderable2DComponent
	{
		glm::vec3 color;
		Render2DType type;
	};

	struct MeshComponent
	{
		std::shared_ptr<Model> model;
	};

	struct CameraComponent
	{
		std::shared_ptr<CameraController> cameraController;
		glm::mat4 view;
		glm::mat4 projection;
		bool primary;
	};

	struct TagComponent
	{
		std::string tag;
	};

}
