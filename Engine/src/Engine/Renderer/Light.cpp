#include "Light.h"

namespace EE {

	Light::Light()
	{
		light.LoadModel("assets/models/lightSphere.obj", "assets/shaders/light.shader");
	}

}


