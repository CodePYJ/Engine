#pragma once

//#include "Light.h"

namespace EE {

	/*class PaarallelLight :public Light
	{
	public:
		virtual void SetLightProperty(LightProperty light_property)  override
		{
			m_light_property = light_property;
			light_uniform_block.light_property_mat4_1 = {
				light_property.ambientStrength, light_property.specularStrength, light_property.specularIndex, 1.0f,
				light_property.lightPos[0], light_property.lightPos[1], light_property.lightPos[2], 1.0f,
				light_property.lightColor[0], light_property.lightColor[1],light_property.lightColor[2], 1.0f,
				light_property.constant,light_property.linear,light_property.quadratic,1.0f
			};
			if (spotlight) {
				light_uniform_block.light_property_mat4_2 = {
					m_spotlight.direction[0], m_spotlight.direction[1], m_spotlight.direction[2], 1.0f,
					m_spotlight.inner_cutoff,m_spotlight.outer_cutoff,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f
				};
			}
		}
	private:


	};*/
}



