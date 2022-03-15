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
		void SetUniform4f(const std::string& name, glm::vec4& value);
		void SetUniformMat4(const std::string& name, glm::mat4& mat4);

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
