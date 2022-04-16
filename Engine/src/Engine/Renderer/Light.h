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

		//À•ºı										æ‡¿Î 50
		float constant = 1.0f;				
		float linear = 0.09f;
		float quadratic = 0.032f;
	};

	struct Spotlight
	{
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
		float inner_cutoff = 0.9f;
		float outer_cutoff = 0.7f;
	};

	struct LightUniformBlock
	{
		glm::mat4 light_property_mat4_1;
		glm::mat4 light_property_mat4_2;
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

		LightUniformBlock light_uniform_block;

	private:
		Model light;
		LightProperty m_light_property;
		Spotlight m_spotlight;
		bool spotlight = true;
	};

}

