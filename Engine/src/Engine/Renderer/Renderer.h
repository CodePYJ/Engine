#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace EE {

	class Renderer
	{
	public:
		void Clear();
		void Draw(VertexArray& vao, IndexBuffer& ebo, Shader& shader);
	};
}

