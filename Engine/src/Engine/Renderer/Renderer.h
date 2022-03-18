#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Engine/Core/Core.h"


namespace EE {

	class EE_API Renderer
	{
	public:
		Renderer();
		void Clear();
		void Draw(VertexArray& vao, IndexBuffer& ebo, Shader& shader);
	};
}

