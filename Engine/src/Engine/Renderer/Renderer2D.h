#pragma once

#include <glm/glm.hpp>
#include "Camera.h"


namespace EE {

	class Renderer2D
	{
	public:
		~Renderer2D();
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const glm::vec4& color);
	};
}
