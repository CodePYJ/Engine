#include "RenderObj.h"


namespace EE {

	RenderObj::RenderObj(float vers[36], std::string path)
		: vertices(vers), shaderPath(path)
	{
		
	}

	void RenderObj::Init(float vers[36], std::string path)
	{
		//for (int i = 0; i < 4; i++) {
		//	position = { vers[i * 9 + 0], vers[i * 9 + 1], vers[i * 9 + 2] };
		//	color = { vers[i * 9 + 3], vers[i * 9 + 4], vers[i * 9 + 5], 1.0f};
		//	normal = { vers[i * 9 + 6], vers[i * 9 + 7], vers[i * 9 + 8] };
		//}
		//rotation = 0.0f;
		//size = { 1.0f,1.0f ,1.0f };
	}

}