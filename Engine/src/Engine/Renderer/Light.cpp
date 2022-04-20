#include "Light.h"

namespace EE {

	Light::Light()
	{
		light.LoadModel("assets/models/lightSphere.obj", "assets/shaders/light.shader");
	}

	void Light::SetLightProperty(LightProperty light_property)
	{
		m_light_property = light_property;
	}

}


