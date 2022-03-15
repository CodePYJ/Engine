#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Engine/Core/Core.h"


namespace EE {

	class EE_API VertexArray
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
