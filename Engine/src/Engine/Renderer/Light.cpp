#include "Light.h"

namespace EE {

	Light::Light()
	{
		light.LoadModel("assets/models/lightSphere.obj", "assets/shaders/light.shader");
	}

	void Light::SetLightProperty(LightProperty light_property)
	{
		m_light_property = light_property;
		light_uniform_block.light_property_mat4_1 = {
			light_property.ambientStrength, light_property.specularStrength, light_property.specularIndex, 1.0f,
			light_property.lightPos[0], light_property.lightPos[1], light_property.lightPos[2], 1.0f,
			light_property.lightColor[0], light_property.lightColor[1],light_property.lightColor[2], 1.0f,
			-1.0f,1.0f,1.0f,1.0f
		};

		if (m_light_type == LightType::PARALLEL_LIGHT) {
			light_uniform_block.light_property_mat4_1[3][0] = 0.0f;
			light_uniform_block.light_property_mat4_2[0][0] = m_parallel_light.direction[0];
			light_uniform_block.light_property_mat4_2[0][1] = m_parallel_light.direction[1];
			light_uniform_block.light_property_mat4_2[0][2] = m_parallel_light.direction[2];
		}
		else if (m_light_type == LightType::POINT_LIGHT) {
			light_uniform_block.light_property_mat4_1[3][0] = 1.0f;
			light_uniform_block.light_property_mat4_2[0][0] = m_point_light.constant;
			light_uniform_block.light_property_mat4_2[0][1] = m_point_light.linear;
			light_uniform_block.light_property_mat4_2[0][2] = m_point_light.quadratic;
		}
		else if (m_light_type == LightType::SPOT_LIGHT) {
			light_uniform_block.light_property_mat4_1[3][0] = 2.0f;
			light_uniform_block.light_property_mat4_2[0][0] = m_spotlight.direction[0];
			light_uniform_block.light_property_mat4_2[0][1] = m_spotlight.direction[1];
			light_uniform_block.light_property_mat4_2[0][2] = m_spotlight.direction[2];
			light_uniform_block.light_property_mat4_2[1][0] = m_spotlight.inner_cutoff;
			light_uniform_block.light_property_mat4_2[1][1] = m_spotlight.outer_cutoff;
		}
	}

}


