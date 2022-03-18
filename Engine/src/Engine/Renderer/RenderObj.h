#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


namespace EE {

	class RenderObj
	{
	public:
		RenderObj(std::string path);

	public:
		std::unique_ptr<EE::VertexArray> VAO;
		std::unique_ptr<EE::Shader> shader;
		std::unique_ptr<EE::IndexBuffer> EBO;

	private:
		std::unique_ptr<EE::VertexBuffer> VBO;
		VertexBufferLayout layout;
		
		std::string shaderPath;
	};
}
