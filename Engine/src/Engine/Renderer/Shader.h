#pragma once

#include "Engine/EEpch.h"
#include <glm/glm.hpp>


struct ShaderSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

namespace EE {

	class Shader
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind();
		void Unbind();

		void SetUniform4f(const std::string& name, glm::vec4& value);

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
