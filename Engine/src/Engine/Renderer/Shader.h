#pragma once

#include "Engine/EEpch.h"
#include <glm/glm.hpp>
#include "Engine/Core/Core.h"


struct  EE_API ShaderSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

namespace EE {

	class EE_API Shader
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind();
		void Unbind();

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, const glm::vec2& value);
		void SetUniform3f(const std::string& name, const glm::vec3& value);
		void SetUniform4f(const std::string& name, const glm::vec4& value);
		void SetUniformMat4(const std::string& name, const glm::mat4& mat4);
		unsigned int GetId() { return m_RendererID; }

	private:
		unsigned int GetUniformLocation(const std::string& name);
		ShaderSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
	};

}
