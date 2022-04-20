#pragma once

#include "Mesh.h"
#include "Model.h"

namespace EE {

	enum class LightType
	{
		PARALLEL_LIGHT = 0, POINT_LIGHT ,SPOT_LIGHT
	};

	struct LightProperty
	{
		int light_type;
		float ambientStrength = 0.3f;
		glm::vec3 lightColor = { 1.0, 1.0, 1.0 };
		glm::vec3 lightPos;

		//ParallelLight
		glm::vec3 parallel_direction = { 0.0f, 0.0f,-1.0f };

		//PointLight
		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;

		//Spotlight
		float inner_cutoff = 0.9f;
		float outer_cutoff = 0.7f;
		glm::vec3 spot_direction = glm::vec3(0.0f, 0.0f, -1.0f);
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

	private:
		Model light;
		LightProperty m_light_property;
		LightType m_light_type = LightType::PARALLEL_LIGHT;
	};

}

