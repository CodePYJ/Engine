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
		glm::vec3 color;

		std::shared_ptr<Renderer2DData> data_ptr;
	};

	struct ShaderComponent
	{
		std::string path;
	};

	struct CameraComponent
	{
		glm::mat4 view;
		glm::mat4 projection;
		std::shared_ptr<OrthCameraController> cameraController;
	};
 
	struct TagComponent
	{
		std::string tag;
	};

}
