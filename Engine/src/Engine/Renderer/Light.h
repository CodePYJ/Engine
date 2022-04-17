#pragma once

#include "Mesh.h"
#include "Model.h"

namespace EE {

	enum class LightType
	{
		PARALLEL_LIGHT = 0, POINT_LIGHT ,SPOT_LIGHT = 2
	};

	struct LightProperty
	{
		float ambientStrength = 0.3f;
		float specularStrength = 0.3f;
		int specularIndex = 32;
		glm::vec3 lightColor = { 1.0, 1.0, 1.0 };	
		glm::vec3 lightPos;
	};

	struct ParallelLight
	{
		glm::vec3 direction = { 0.0f,0.0f,-1.0f };
	};

	struct PointLight
	{
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
		virtual ~Light() = default;

		Model& GetLight() { return light; }

		LightProperty GetLightProperty() { return m_light_property; }
		void SetLightProperty(LightProperty light_property);


		LightType& GetLightType() { return m_light_type; }
		void SetLightType(int light_type) { m_light_type = (LightType)light_type; }

		ParallelLight m_parallel_light;
		PointLight m_point_light;
		Spotlight m_spotlight;
		LightUniformBlock light_uniform_block;

	private:
		Model light;
		LightProperty m_light_property;
		LightType m_light_type = LightType::PARALLEL_LIGHT;

	};

}

