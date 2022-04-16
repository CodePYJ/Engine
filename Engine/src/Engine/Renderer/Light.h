#pragma once

#include "Mesh.h"
#include "Model.h"

namespace EE {

	struct LightProperty											
	{																		
		float ambientStrength = 0.3f;
		float specularStrength = 0.3f;
		int specularIndex = 32;
		glm::vec3 lightColor = { 1.0, 1.0, 1.0 };		
		glm::vec3 lightPos;
	};																		

	class Light
	{
	public:
		Light();

		Model& GetLight() { return light; }

		LightProperty GetLightProperty() { return m_light_property; }
		void SetLightProperty(LightProperty light_property)
		{ 
			m_light_property = light_property; 
			light_property_mat4 = {
				light_property.ambientStrength, light_property.specularStrength, light_property.specularIndex, 1.0f,
				light_property.lightPos[0], light_property.lightPos[1], light_property.lightPos[2], 1.0f,
				light_property.lightColor[0], light_property.lightColor[1],light_property.lightColor[2], 1.0f,
				1.0f,1.0f,1.0f,1.0f
			};
		}

		glm::mat4 light_property_mat4;

	private:
		Model light;
		LightProperty m_light_property;
	};

}

