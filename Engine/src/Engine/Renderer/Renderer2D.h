#pragma once

#include <glm/glm.hpp>
#include "RenderObj.h"

namespace EE {

	class Renderer2D
	{
	public:
		static unsigned int CreatObj(float vers[36], std::string path);
		static void Shutdown();

		static void BeginScene(unsigned int objID, OrthographicCamera& camera);
		static void EndScene();

		static RenderObj* GetObj(unsigned int objID);

		// Primitives
		static void DrawQuad(glm::vec3 lightPos);

		static int LatestObjID;
	private:
		static std::vector<RenderObj*> RenderObjs;
		static RenderObj* currentObj;
		//static glm::vec3 lightPos;
	};
}
