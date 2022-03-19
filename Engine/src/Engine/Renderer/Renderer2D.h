#pragma once

#include <glm/glm.hpp>
#include "RenderObj.h"

namespace EE {

	class Renderer2D
	{
	public:
		static unsigned int CreatObj(std::string path);
		static void Shutdown();

		static void BeginScene(unsigned int objID, OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad2U(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& lightColor , const glm::vec4& objectColor);
		static void DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const glm::vec4& color);

	private:
		static RenderObj* currentObj;
		static std::vector<RenderObj*> RenderObjs;
		static int LatestObjID;
	};
}
