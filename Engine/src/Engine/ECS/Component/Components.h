#pragma once

#include "Engine/EEpch.h"
#include <glm/glm.hpp>

#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/CameraController.h"


namespace EE {

	struct TransformComponent
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	struct Renderable2DComponent
	{
		std::shared_ptr<Renderer2DData> data_ptr;
		glm::vec3 color;
		glm::mat4 ViewProjection;
	};

	struct ShaderComponent
	{
		std::string path;
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
