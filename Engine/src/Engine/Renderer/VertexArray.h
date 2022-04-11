#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Engine/Core/Core.h"
#include "IndexBuffer.h"

namespace EE {

	class EE_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);
		void AddEBO(std::shared_ptr<IndexBuffer>& ebo);
		void Bind();
		void Unbind();

		IndexBuffer GetEBO() { return *m_EBO; }

		private:
			unsigned int m_RendererID;
			std::shared_ptr<IndexBuffer> m_EBO;
	};
}
