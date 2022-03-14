#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace EE {

	class VertexArray 
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);
		void Bind();
		void Unbind();

		private:
			unsigned int m_RendererID;
	};
}
